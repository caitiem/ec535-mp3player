#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <dirent.h>

static long BEATS[1024];
struct pollfd poll_fd;
struct sigaction action;
int oflags;
void sighandler(int);
void setupHandler();
int sigFile;
int handled_sigio = 0;
char button_mode[10];
char songlist[100][256];

int main(int argc, char **argv) {
	srand(time(NULL));
	char line[256];
	char song[256];
	int ii, j, count = 0;
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
	
    setupHandler();

	DIR *dir;
	struct dirent *ent;

	char temp[256];
	int count=0;
	if ((dir = opendir ("/mnt/card/audio")) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    //printf ( ent->d_name);
	    strcpy(temp,ent->dname);
	  
	    for(i=0;i<strlen(temp);i++)
	    {
	    	if(temp[i]=='.')
	    	{
	    		temp[i]='\0';
	    		break;
	    	}
	    }
	    strcpy(songlist[count],temp);
	    count++;
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	
    if(shuffle)
    {

	int songNum = rand()%count; 

    }
    else
    {
    	
    	
    }
    fp = fopen("/mnt/card/beats/learntofly.txt", "r");
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
    /*for (j=0; j<i; j++)
    {
		pFile = fopen("/dev/mp3play", "r+");
        sprintf(tempstr, "%d", BEATS[j]);
        fputs(tempstr, pFile);
        printf("USER LEVEL: wrote BEATS[%d] = %li\n", j, BEATS[j]);
		fclose(pFile);
    }
	pFile = fopen("/dev/mp3play", "r+");*/
    printf("USER LEVEL: all beats written to kernel\n");
    while(1) {
    	if (handled_sigio) {
    		printf("pausing\n");
    		handled_sigio = 0;
    		pause();
    	}
    }
    //close(sigFile);
	//sending the "R" will be once Caitie says to play the song
	
	//fclose(pFile);
	
	//system("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:- | aplay -D creative");
 
	/*pid_t pid=fork();
    if (pid==0) { // child
        //fputs("R", pFile);
    }
    else { // parent
    	system("./madplay /mnt/card/audio/learntofly.mp3 -r 44100 --output=wave:- | aplay -D creative");
        waitpid(pid,0,0);
    }*/

	return 0;
}

void setupHandler() {
	poll_fd.fd = sigFile;
    poll_fd.events = POLLIN; // check for normal or out-of-band
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
	printf("got an async\n");
    read(sigFile,  button_mode, 10);
    printf("%s\n", button_mode);
    handled_sigio = 1;
}
