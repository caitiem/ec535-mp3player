#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct
{
    int beat;
    int lights;
} BEAT_DATA;

static long BEATS[1024];


int main(int argc, char **argv) {
	char line[256];
	int ii, j, count = 0;
	int i;
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
    
   // printf("BEATS[0] * 1000000 = %li\n", BEATS[0]);
    i = 1;
    while (fgets(tempstr, 15, fp)!=NULL)
    {
        
        //BEATS[i] = atof(tempstr);
        tempfloat = atof(tempstr);
        tempfloat = tempfloat * 1000000;
        BEATS[i] = tempfloat - prevNum;
        prevNum = tempfloat;
//        BEATS[i] = tempfloat;
  //      BEATS[i] = BEATS[i] - BEATS[i-1];
        //BEATS[i] = BEATS[i] * 1000000; //convert to microseconds
        i++;
    }
    fclose(fp);
    printf("USER LEVEL: read all beats\n");
    //ALL beats are in the BEATS file.  now need to write it to /dev/mp3play
    for (j=0; j<i; j++)
    {
        sprintf(tempstr, "%d", BEATS[j]);
        fputs(tempstr, pFile);
        printf("USER LEVEL: wrote BEATS[%d] = %li\n", j, BEATS[j]);
    }
    printf("USER LEVEL: all beats written to kernel\n");
    fputs("R", pFile);
    
    /*
	if (argc == 2 && (atoi(argv[1]) != 0)) {
		printf("\nValue\tSpeed\tState\tDirection\tBrightness\n");
	    while(1)
	    {
	        fclose(pFile);
	        pFile = fopen("/dev/mygpio", "r+");
	    	fgets(line, 256, pFile);
	    	printf("%s", line);
	    	sleep(atoi(argv[1]));
	    }
	
	}*/

	fclose(pFile);
	return 0;
}
