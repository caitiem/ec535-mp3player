#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

static long BEATS[1024];
struct sigaction action;
int oflags;
void sighandler(int);
void setupHandler(int);
int handled_sigio = 0;
char songlist[100][256];
int playing = 0;
int have_written = 0;
int mystdin = 0;
int mystdout = 1;
#define mymp3fifo "/tmp/mymp3fifo"
int songNum=1;
char beatpath[256];
char audiopath[256];
int songCount=0;
pid_t madPID;
pid_t aplayPID;
char line[256];
char song[256];
int ii, j;
int i,shuffle=0;
char tempstr[15];
float tempfloat;
float prevNum;
int shuffleSong = 0;
int madpipe;
int loadSong(int);
int playSong(int);
void quitMadplay();
void quitAplay();

void cleanup_mymp3fifo(int sig){
	quitMadplay();
	unlink(mymp3fifo);
	quitAplay();
	exit(0);
}

int main(int argc, char **argv) {
	srand(time(NULL));

	FILE * pFile;
	pFile = fopen("/dev/mp3play", "r+");
	if (pFile==NULL) {
		fputs("mp3play module isn't loaded\n",stderr);
		return -1;
	}
	fclose(pFile);
	int sigFile;
	sigFile = open("/dev/mp3play", O_RDWR, 7777);
	if (sigFile==-1) {
		fputs("mp3play module isn't loaded\n",stderr);
		return -1;
	}

	setupHandler(sigFile);

	printf("made fifo with return = %d\n", mkfifo(mymp3fifo, 0666));
	signal(SIGINT, cleanup_mymp3fifo); 	

	DIR *dir;
	struct dirent *ent;

	char temp[256];
	songCount=0;
	if ((dir = opendir ("/mnt/card/audio")) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    //printf ( ent->d_name);
	    strcpy(temp,ent->d_name);
	  
	    for(i=0;i<strlen(temp);i++)
	    {
	    	if(temp[i]=='.')
	    	{
	    		temp[i]='\0';
	    		break;
	    	}
	    }
	    if(songCount>1)
	    	strcpy(songlist[songCount-2],temp);
	    songCount++;
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	songCount-=2;
	
	int xx;
	for(xx = 0; xx < songCount; xx++) {
		printf("%d %s\n", xx, songlist[xx]);
	}

	playSong(songNum);

	pause();
	while(1) {
		if (handled_sigio) {
			printf("handling sigio\n");
			handled_sigio = 0;
			if(shuffleSong) {
				shuffleSong = 0;
				quitMadplay();
				//quitAplay();
				playSong(songNum);
			}
			printf("while loop pausing\n");
			pause();
		}
	}

	printf("should never get here.\n");

	return 0;
}

void setupHandler(int sigFile) {
    // Setup signal handler
    memset(&action, 0, sizeof(action));
    action.sa_handler = sighandler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    sigaction(SIGIO, &action, NULL);
    fcntl(sigFile, F_SETOWN, getpid());
    oflags = fcntl(sigFile, F_GETFL);
    fcntl(sigFile, F_SETFL, oflags | FASYNC);
}

void quitMadplay() {
	printf("Quitting madplay.");
	madpipe = open("/tmp/mymp3fifo", O_WRONLY);
	printf("madpipe opened = %d\n", madpipe);
	write(madpipe, "q", 1);
	close(madpipe);
	//usleep(100*1000);
	system("killall madplay");
	printf("killed madplay\n");
}

void quitAplay() {
	printf("Quitting aplay.");
	system("killall aplay");
}

// SIGIO handler
void sighandler(int signo)
{
	char button_mode[5];
	//printf(stdout, "got an async\n");
	FILE * readKernFile;
	readKernFile = fopen("/dev/mp3play", "r+");
	//fgets(button_mode, 10, readKernFile);
    //read(sigFile,  button_mode, 10);
	fread(button_mode, 1, 5, readKernFile);
	fclose(readKernFile);
	printf("got async\n");
    //printf("button is %s\n", button_mode);
	printf("button_mode = %s\n", button_mode);
	if (button_mode[0] == '0') {
		// play/pause called
		printf("play/pause\n");
		madpipe = open("/tmp/mymp3fifo", O_WRONLY);
		printf("madpipe opened = %d\n", madpipe);
		write(madpipe, "p", 1);
		close(madpipe);
		/*if(playing)
		{
			FILE * kernelFile;
			kernelFile = fopen("/dev/mp3play", "r+");
			if (kernelFile!=NULL) {
				playing=0;
				fputs("A", kernelFile);
				fclose(kernelFile);
			}
		}
		else
		{
			FILE * kernelFile;
			kernelFile = fopen("/dev/mp3play", "r+");
			if (kernelFile!=NULL) {
				playing=1;
				fputs("P", kernelFile);
				fclose(kernelFile);
			}
		}*/			
	}
	else if (button_mode[0] == '1') {
		printf("Shuffling\n");
		FILE * kernelFile;
		kernelFile = fopen("/dev/mp3play", "r+");
		if (kernelFile!=NULL) {
			fputs("F", kernelFile);
			fclose(kernelFile);
		}

		shuffleSong = 1;
			
		songNum = rand()%songCount;
	}
	else if (button_mode[0] == '2') {
		printf("increasing volume\n");
		madpipe = open("/tmp/mymp3fifo", O_WRONLY);
		printf("madpipe opened = %d\n", madpipe);
		write(madpipe, "+", 1);  
		close(madpipe);
	}
	else if (button_mode[0] == '3') {
		printf("decreasing volume\n");
		madpipe = open("/tmp/mymp3fifo", O_WRONLY);
		printf("madpipe opened = %d\n", madpipe);
		write(madpipe, "-", 1);  
		close(madpipe);
	}
	printf("setting handled_sigio\n");
    handled_sigio = 1;
}

int loadSong(int songNum) {
	sprintf(beatpath,"/mnt/card/beats/%s.txt",songlist[songNum]);
	sprintf(audiopath,"/mnt/card/audio/%s.mp3",songlist[songNum]);
	FILE * fp;
    fp = fopen(beatpath, "r");
    if (fp == NULL)
    {
        fputs("Error opening file\n", stderr);
        return(-1);
    }
    fgets(tempstr, 15, fp);
    tempfloat = atof(tempstr);
    printf("tempfloat = %f\n", tempfloat);
    tempfloat = tempfloat * 1000000;
    prevNum = tempfloat;
    BEATS[0] = tempfloat;
    //printf("tempstr 0 = %s\n", tempstr);
    //printf("BEATS[0] = %lf\n", BEATS[0]);
    
    i = 1;
    while (fgets(tempstr, 15, fp)!=NULL)
    {
        tempfloat = atof(tempstr);
        tempfloat = tempfloat * 1000000;
        BEATS[i] = tempfloat - prevNum;
        prevNum = tempfloat;
        i++;
    }
    fclose(fp);
    printf("USER LEVEL: read all beats\n");
    //ALL beats are in the BEATS file.  now need to write it to /dev/mp3play
	FILE * pFile;
    for (j=0; j<i; j++)
    {
		pFile = fopen("/dev/mp3play", "r+");
        sprintf(tempstr, "%d", BEATS[j]);
        fputs(tempstr, pFile);
        //printf("USER LEVEL: wrote BEATS[%d] = %li\n", j, BEATS[j]);
		fclose(pFile);
    }
    printf("USER LEVEL: all beats written to kernel\n");
	sprintf(beatpath,"/mnt/card/beats/%s.txt",songlist[songNum]);
	sprintf(audiopath,"/mnt/card/audio/%s.mp3",songlist[songNum]);

	return 0;
}

int playSong(int songNum)
{
	//system("killall madplay");
	//system("killall aplay");
	loadSong(songNum);
	int mad_to_aplay_pipe_fd[2];
	int user_to_mad_pipe_fd[2];
	pipe(user_to_mad_pipe_fd);
	pipe(mad_to_aplay_pipe_fd);

	pid_t my_pid;
	pid_t my_pid2;
	char *madplayargv[] = {"madplay", audiopath, "-r", "44100", "--repeat=1", "--tty-control", "--output=wave:-", NULL };
	char *aplayargv[] = {"aplay", "-D", "creative", NULL };
	//char *aplayargv[] = {"/usr/bin/aplay", "--help", NULL};
	if((my_pid = fork()) == -1)
	{
	        perror("fork");
	        exit(1);
	}

	if(my_pid == 0)
	{

		if((my_pid2 = fork()) == -1)
		{
			    perror("fork");
			    exit(1);
		}

		if(my_pid2 == 0) {
			/* Child process closes up input side of pipe */
			printf("in mad child process\n");
			dup2(mad_to_aplay_pipe_fd[1], mystdout);
			close(mad_to_aplay_pipe_fd[1]);
			//dup2(user_to_mad_pipe_fd[0], mystdin);
			//close(user_to_mad_pipe_fd[0]);
			execve("/usr/bin/madplay", madplayargv, NULL);
			printf("something bad has happened with madplay child\n");
			// | aplay -D creative
			//execv("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:-", NULL);
		} else {
			printf("my aplay second child\n");
			dup2(mad_to_aplay_pipe_fd[0], mystdin);
			close(mad_to_aplay_pipe_fd[0]);
			playing = 1;
			execve("/usr/bin/aplay", aplayargv, NULL);
			printf("something bad has happened with aplay child\n");
		}
	    
	}
	else
	{
	
	    printf("in parent process\n");
		return 0;
		//dup2(user_to_mad_pipe_fd[1], mystdout);
		//close(user_to_mad_pipe_fd[1]);
		/*pause();
		while(1) {
			if (handled_sigio) {
				handled_sigio = 0;
				pause();
			}
		}*/
	}
	
}
