#include <linux/init.h>
#include <linux/module.h>
#include <asm/hardware.h>
#include <asm/uaccess.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/pxa-regs.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/jiffies.h> /* jiffies */
#include <linux/delay.h>
#include <linux/random.h>
#include <linux/poll.h>
#include <linux/wait.h>

MODULE_LICENSE("Dual BSD/GPL");

static int mp3play_init(void);
static void mp3play_exit(void);

static ssize_t mp3play_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos);
static ssize_t mp3play_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static int mp3play_open(struct inode *inode, struct file *filp);
static int mp3play_release(struct inode *inode, struct file *filp);
static int mp3play_fasync(int fd, struct file *filp, int mode);

static unsigned int irqNumber0; ///< Used to share the IRQ number within this file
static unsigned int irqNumber1;
static unsigned int irqNumber2;
static unsigned int irqNumber3;
static irq_handler_t but0_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but1_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but2_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but3_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

static unsigned int irqNumber0; ///< Used to share the IRQ number within this file
static unsigned int irqNumber1;
static unsigned int irqNumber2;
static unsigned int irqNumber3;
static irq_handler_t but0_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but1_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but2_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t but3_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

// output LED pins
static int led0 = 16;
static int led1 = 29; 
static int led2 = 30;
static int led3 = 31;

// Input button pins
static int playpause0 = 117;
static int shuffle1 = 101;
static int volumeup2 = 28;
static int volumedown3 = 113;

//button state variables
static int state0 = 0;
static int state1 = 0;
static int state2 = 0;
static int state3 = 0;

//state variable
static int nowPlaying = 0;

static unsigned int counter;
static long BEATS[1024];
static int iterator = 0;
static int numBeats;
static int paused_index;

static struct timer_list beatTime;
static void beatTime_handler(unsigned long data);
static void pause_beatTime(struct timer_list);
static void restart_beatTime(struct timer_list);
static void stop_beatTime(struct timer_list);
// async stuff
static DECLARE_WAIT_QUEUE_HEAD(mp3play_wait);
struct fasync_struct *async_queue; /* asynchronous readers */

struct file_operations mp3play_fops = {
	write: mp3play_write, 
	read:  mp3play_read,
	open: mp3play_open,
	release: mp3play_release,
	fasync: mp3play_fasync
};

/* Declaration of the init and exit functions */
module_init(mp3play_init);
module_exit(mp3play_exit);

static int mp3play_init(void)
{
    int result;
    
	/* Registering device */
	result = register_chrdev(61, "mp3play", &mp3play_fops);
	if (result < 0)
	{
		printk(KERN_ALERT"mp3play: cannot obtain major number 61\n");
		return result;
	}
    
    //initialize gpio pins 28, 29, 30, & 31 as output pins
    pxa_gpio_mode(led0 | GPIO_OUT);
    pxa_gpio_mode(led1 | GPIO_OUT);
    pxa_gpio_mode(led2 | GPIO_OUT);
    pxa_gpio_mode(led3 | GPIO_OUT);
   
    pxa_gpio_set_value(led0, 0);
    pxa_gpio_set_value(led1, 0);
	pxa_gpio_set_value(led2, 0);
	pxa_gpio_set_value(led3, 0);

    //initialize gpio pins 17 & 101 as input pins
    pxa_gpio_mode(playpause0);
    pxa_gpio_mode(shuffle1);
    pxa_gpio_mode(volumeup2);
	pxa_gpio_mode(volumedown3);
    
    //setup timer
    //setup_timer(&beatTime, beatTime_handler, 0);
    irqNumber0 = gpio_to_irq(playpause0);
	irqNumber1 = gpio_to_irq(shuffle1);
	irqNumber2 = gpio_to_irq(volumeup2);
    irqNumber3 = gpio_to_irq(volumedown3);
        
    result = request_irq(irqNumber0, (irq_handler_t) but0_irq_handler, IRQF_TRIGGER_RISING, "but0_handler", NULL);
    result = request_irq(irqNumber1, (irq_handler_t) but1_irq_handler, IRQF_TRIGGER_RISING, "but1_handler", NULL);
    result = request_irq(irqNumber2, (irq_handler_t) but2_irq_handler, IRQF_TRIGGER_RISING, "but2_handler", NULL);
    result = request_irq(irqNumber3, (irq_handler_t) but3_irq_handler, IRQF_TRIGGER_RISING, "but3_handler", NULL);

    printk(KERN_ALERT "Module initialized\n");
    
    return 0;
}

static void mp3play_exit(void)
{
    pxa_gpio_set_value(led0, 0);
    pxa_gpio_set_value(led1, 0);
	pxa_gpio_set_value(led2, 0);
	pxa_gpio_set_value(led3, 0);
	
    del_timer(&beatTime);
    
    unregister_chrdev(61, "mp3play");
    
    printk(KERN_ALERT "Module exited\n");	
}

static int mp3play_open(struct inode *inode, struct file *filp)
{
	/* Success */
	return 0;
}

static int mp3play_release(struct inode *inode, struct file *filp)
{	
	mp3play_fasync(-1, filp, 0);
	/* Success */
	return 0;
}

static int mp3play_fasync(int fd, struct file *filp, int mode) {
	//printk(KERN_ALERT "in fasync\n");
	return fasync_helper(fd, filp, mode, &async_queue);
}

static ssize_t mp3play_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos)
{
    char tbuf[15], *tbptr = tbuf;


	// Create input buffer
	char * buffer = (char*)kmalloc(len, GFP_KERNEL);
	memset(buffer, 0, len);

	// Get input from user space
	if (copy_from_user(buffer + *f_pos, buf, len))
		return -EFAULT;
	
	//printk(KERN_ALERT "KERNEL SPACER: buffer = %s\n", buffer);
	if (buffer[0] == 'R')
	{
		if (nowPlaying == 0)
		{
		    //reached end of data to be written to array
		    //can initialize first timer now
		    nowPlaying = 1;
			setup_timer(&beatTime, beatTime_handler, 0);
			numBeats = iterator;
		    iterator = 0;
		    printk(KERN_ALERT "nowPlaying\n");
		    mod_timer(&beatTime, jiffies + usecs_to_jiffies(BEATS[iterator]));
		    iterator++;
		}
		//printk(KERN_ALERT "IN WRITE, found R\n");
	}
	else if(buffer[0] == 'S')
	{
		del_timer(&beatTime);
		
		nowPlaying = 0;
		iterator=0;
		memset(BEATS,0,sizeof(long)*1024);
		
	}
	else
	{
	     tbptr = &buffer[0];
	     //printk(KERN_ALERT "IN WRITE, reading data into %d\n", iterator);
	     BEATS[iterator] = simple_strtol(tbptr, NULL, 10);
	     iterator++;
	}
	
	
    return len;
}
static ssize_t mp3play_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    char tbuf[256], *tbptr = tbuf;
    
    if (state0) {
    	state0 = 0;
    	tbptr += sprintf(tbptr, "0");
    } else if (state1) {
    	state1 = 0;
    	tbptr += sprintf(tbptr, "1");
    } else if (state2) {
    	state2 = 0;
    	tbptr += sprintf(tbptr, "2");
    } else if (state3) {
    	state3 = 0;
    	tbptr += sprintf(tbptr, "3");
    }    

    if (copy_to_user(buf, tbuf, strlen(tbuf)))
	{
		printk("error\n");
		return -EFAULT;
	}
    *f_pos = strlen(tbuf);
	return strlen(tbuf);
}

static void beatTime_handler(unsigned long data)
{
    //do a thing with setting new expiration time and which lights should go on
    get_random_bytes(&counter, sizeof(unsigned int));
    counter = counter % 15;
	counter++;
    //printk(KERN_ALERT "IN TIMER HANDLER\n");
    //printk(KERN_ALERT "counter = %d\n", counter);
    gpio_set_value(led0, counter & 1);
	gpio_set_value(led1, (counter & 2)>>1);
	gpio_set_value(led2, (counter & 4)>>2);
	gpio_set_value(led3, (counter & 8)>>3);
	if (iterator < numBeats)
	{
    	mod_timer(&beatTime, jiffies + usecs_to_jiffies(BEATS[iterator]));
    	iterator++;
 	}
	else
	{
		//song over
		pxa_gpio_set_value(led0, 0);
    	pxa_gpio_set_value(led1, 0);
		pxa_gpio_set_value(led2, 0);
		pxa_gpio_set_value(led3, 0);

		nowPlaying = 0;
	}   
}

static irq_handler_t but0_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	state0 = 1;
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
    return (irq_handler_t) IRQ_HANDLED; 
}
static irq_handler_t but1_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	state1 = 1;
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
    return (irq_handler_t) IRQ_HANDLED; 
}
static irq_handler_t but2_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	state2 = 1;
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
    return (irq_handler_t) IRQ_HANDLED; 
}
static irq_handler_t but3_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	state3 = 1;
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	return (irq_handler_t) IRQ_HANDLED; 
}
static void pause_beatTime(struct timer_list timer)
{
	paused_index=iterator;
	del_timer(&timer);
	
}
static void restart_beatTime(struct timer_list);
{
	setup_timer(&beatTime, beatTime_handler, 0);
	mod_timer(jiffies + usecs_to_jiffies(BEATS[paused_index]);
}
static void stop_beatTime(struct timer_list)
{
	del_timer(&timer);
	iterator=0;
	
}
