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

MODULE_LICENSE("Dual BSD/GPL");

static int mp3play_init(void);
static void mp3play_exit(void);

static ssize_t mp3play_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos);
static ssize_t mp3play_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);

// output LED pins
static int led0 = 16;
static int led1 = 29; 
static int led2 = 30;
static int led3 = 31;

// Input button pins
static int but0 = 17;
static int but1 = 101;
static int but2 = 28;
static int but3 = 113;

//temp.  song name.  for song append .mp3 and for beats append .txt
//static char SONG[11] = "learntofly";
static int counter;
static long BEATS[1024];
static int iterator = 0;

static struct timer_list beatTime;
static void beatTime_handler(unsigned long data);

struct file_operations mp3play_fops = {
	write: mp3play_write, 
	read:  mp3play_read
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
    
   
    //initialize gpio pins 17 & 101 as input pins
    pxa_gpio_mode(but0);
    pxa_gpio_mode(but1);
    pxa_gpio_mode(but2);
    
    //setup timer
    setup_timer(&beatTime, beatTime_handler, 0);
    
    
        
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

static ssize_t mp3play_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos)
{
    char tbuf[15], *tbptr = tbuf;


	// Create input buffer
	char * buffer = (char*)kmalloc(len, GFP_KERNEL);
	memset(buffer, 0, len);

	// Get input from user space
	if (copy_from_user(buffer + *f_pos, buf, len))
		return -EFAULT;
		
	if (buffer[0] == 'R')
	{
	    //reached end of data to be written to array
	    //can initialize first timer now
	    iterator = 0;
	    printk(KERN_ALERT "IN WRITE, found R\n");
	    mod_timer(&beatTime, jiffies + usecs_to_jiffies(BEATS[iterator]));
	    iterator++;
	}
	else
	{
	     tbptr = &buffer[0];
	     printk(KERN_ALERT "IN WRITE, reading data into %d\n", iterator);
	     BEATS[iterator] = simple_strtol(tbptr, NULL, 10);
	     iterator++;
	}
	
	
    return len;
}
static ssize_t mp3play_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    return 0;
}

static void beatTime_handler(unsigned long data)
{
    //do a thing with setting new expiration time and which lights should go on
    mod_timer(&beatTime, jiffies + usecs_to_jiffies(BEATS[iterator]));
//    counter = rand() % 16;
    get_random_bytes(&counter, sizeof(int));
    counter = counter % 16;
    printk(KERN_ALERT "IN TIMER HANDLER\n");
    printk(KERN_ALERT "counter = %d\n", counter);
    gpio_set_value(led0, counter & 1);
	gpio_set_value(led1, (counter & 2)>>1);
	gpio_set_value(led2, (counter & 4)>>2);
	gpio_set_value(led3, (counter & 8)>>3);
	msleep(250);
	pxa_gpio_set_value(28, 0);
	pxa_gpio_set_value(29, 0);
	pxa_gpio_set_value(30, 0);
	pxa_gpio_set_value(31, 0);
    iterator++;
    
}
