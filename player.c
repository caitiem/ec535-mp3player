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
void setupHandler();
int sigFile;
int handled_sigio = 0;
char button_mode[10];
char songlist[100][256];
int playing = 0;
int mad_to_aplay_pipe_fd[2];
int user_to_mad_pipe_fd[2];
int have_written = 0;
int mystdin = 0;
int mystdout = 1;
char *mymp3fifo = "/tmp/mymp3fifo";
int madpipe;
int songNum=6;
char beatpath[256];
char audiopath[256];
int songCount=0;
pid_t madPID;
pid_t aplayPID;
int main(int argc, char **argv) {
	srand(time(NULL));
	char line[256];
	char song[256];
	int ii, j;
	int i,shuffle=0;
    char tempstr[15];
    float tempfloat;
    float prevNum;


	FILE * pFile;
	FILE * fp;
	pFile = fopen("/dev/mp3play", "r+");
	if (pFile==NULL) {
		fputs("mp3play module isn't loaded\n",stderr);
		return -1;
	}
	sigFile = open("/dev/mp3play", O_RDWR, 7777);
	if (sigFile==-1) {
		fputs("mp3play module isn't loaded\n",stderr);
		return -1;
	}

	mkfifo(mymp3fifo, 0666);
	
    setupHandler();

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
	sprintf(beatpath,"/mnt/card/beats/%s.txt",songlist[songNum]);
	sprintf(audiopath,"/mnt/card/audio/%s.mp3",songlist[songNum]);
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
    printf("tempstr 0 = %s\n", tempstr);
    printf("BEATS[0] = %lf\n", BEATS[0]);
    
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
	fclose(pFile);
    for (j=0; j<i; j++)
    {
		pFile = fopen("/dev/mp3play", "r+");
        sprintf(tempstr, "%d", BEATS[j]);
        fputs(tempstr, pFile);
        //printf("USER LEVEL: wrote BEATS[%d] = %li\n", j, BEATS[j]);
		fclose(pFile);
    }
	pFile = fopen("/dev/mp3play", "r+");
    printf("USER LEVEL: all beats written to kernel\n");
    fclose(pFile);
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
			
			madPID=my_pid2;
			execve("/usr/bin/madplay", madplayargv, NULL);
			printf("something bad has happened with madplay child\n");
			// | aplay -D creative
			//execv("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:-", NULL);
		} else {
			dup2(mad_to_aplay_pipe_fd[0], mystdin);
		    close(mad_to_aplay_pipe_fd[0]);
			execve("/usr/bin/aplay", aplayargv, NULL);
			printf("something bad has happened with aplay child\n");
		}
        
    }
    else
    {
		
		
        printf("in parent process\n");
		playing = 1;
		aplayPID=my_pid;
		//dup2(user_to_mad_pipe_fd[1], mystdout);
    	//close(user_to_mad_pipe_fd[1]);
		if (have_written == 0) {
			FILE * kernelFile;
			//usleep(2000000);
			kernelFile = fopen("/dev/mp3play", "r+");
			if (kernelFile!=NULL) {
				fputs("R", kernelFile);
				fclose(kernelFile);
				have_written = 1;
			}
		}
		pause();
		while(1) {
			if (handled_sigio) {
				//printf("handled sigio\n");
				handled_sigio = 0;
				pause();
			}
		}
		/*
		}*/
    }

	//system("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:- | aplay -D creative");
   
    //close(sigFile);
	//sending the "R" will be once Caitie says to play the song
 
	/*pid_t pid=fork();
    if (pid==0) { // child
        //fputs("R", pFile);
    }
    else { // parent
    	system("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:- | aplay -D creative");
        waitpid(pid,0,0);
    }*/

	unlink(mymp3fifo);

	return 0;
}

void setupHandler() {
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

// SIGIO handler
void sighandler(int signo)
{
	//printf(stdout, "got an async\n");
    read(sigFile,  button_mode, 10);
    //printf("%s\n", button_mode);
	if (strcmp(button_mode, "0") == 0) {
		// play/pause called
		madpipe = open(mymp3fifo, O_WRONLY);     
		write(madpipe, "p", 1);  
		printf("play/pause\n");
		close(madpipe);
		if(playing)
		{
			playing=0;
			FILE * kernelFile;
			kernelFile = fopen("/dev/mp3play", "r+");
			if (kernelFile!=NULL) {
				fputs("A", kernelFile);
				fclose(kernelFile);
			}
		}
		else
		{
			playing=1;
			FILE * kernelFile;
			kernelFile = fopen("/dev/mp3play", "r+");
			if (kernelFile!=NULL) {
				fputs("P", kernelFile);
				fclose(kernelFile);
			}
		}
		
			
	}
	else if (strcmp(button_mode, "1") == 0) {
		printf("Shuffling\n");
		songNum = rand()%songCount;
		sprintf(beatpath,"/mnt/card/beats/%s.txt",songlist[songNum]);
		sprintf(audiopath,"/mnt/card/audio/%s.mp3",songlist[songNum]);
		FILE * kernelFile;
		kernelFile = fopen("/dev/mp3play", "r+");
		if (kernelFile!=NULL) {
			fputs("F", kernelFile);
			fclose(kernelFile);
		}	
			
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
				system("killall madplay");
				execve("/usr/bin/madplay", madplayargv, NULL);
				printf("something bad has happened with madplay child\n");
				// | aplay -D creative
				//execv("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:-", NULL);
			} else {
				printf("my aplay second child\n");
				dup2(mad_to_aplay_pipe_fd[0], mystdin);
				close(mad_to_aplay_pipe_fd[0]);
				playing = 1;
				system("killall aplay");
				execve("/usr/bin/aplay", aplayargv, NULL);
				printf("something bad has happened with aplay child\n");
			}
		    
		}
		else
		{
		
		
		    printf("in parent process\n");
			
			//dup2(user_to_mad_pipe_fd[1], mystdout);
			//close(user_to_mad_pipe_fd[1]);
			if (have_written == 0) {
				FILE * kernelFile;

				kernelFile = fopen("/dev/mp3play", "r+");
				if (kernelFile!=NULL) {
					fputs("R", kernelFile);
					fclose(kernelFile);
					have_written = 1;
				}
			}
		}
			
	}
	else if (strcmp(button_mode, "2") == 0) {
		madpipe = open(mymp3fifo, O_WRONLY);     
		write(madpipe, "+", 1);  
		printf("increasing volume\n");
		close(madpipe);
	}
	else if (strcmp(button_mode, "3") == 0) {
		madpipe = open(mymp3fifo, O_WRONLY);     
		write(madpipe, "-", 1);  
		printf("decreasing volume\n");
		close(madpipe);
	}
    handled_sigio = 1;
}