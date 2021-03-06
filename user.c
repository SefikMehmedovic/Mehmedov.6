//user.c
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>


//shared memory key
#define SHMKEY 321800

//time struct 
typedef struct {
    unsigned int seconds;
    unsigned int nanoSeconds;
} clockTime;

//shared memory struct
typedef struct {
    int sharedPID[18];       
    int checkProcNum[18];
    int processAddCalled[18];
    int processRW[18];
    int processCallCount[18];
} shared_t;


int sharedShmid;
shared_t *sharedShmptr; 
key_t key; 
int msgid; 
int PIDHolder[18] = {}; 

//function prototypes
void ctrlCHandler(int signal);
void cleanUp();
void messageQueue();

int main(int argc, char* argv[]) {
	// CTRL+C signal handlers
	signal(SIGINT, ctrlCHandler);
 
 
 
     //shared mememory
    sharedShmid = shmget(SHMKEY, sizeof(clockTime), IPC_CREAT|0777);
    if(sharedShmid < 0)
    {
        perror("Shmget error in oss \n");
        exit(0);
    }
    sharedShmptr = shmat(sharedShmid, NULL, 0);
    if(sharedShmptr < 0){
        perror("Shmat error in oss\n");
        exit(0);
    }

 //-----message queue
 messageQueue();
 
 return 0;// main return
 } //main
 
 //-----
 void messageQueue(){
        //generate unique key
        key = ftok("oss", 10);
        //message queue
       
        msgid = msgget(key, 0666 | IPC_CREAT);
}
 
 
 
 //-------------
 //Ctrl+C handler
void ctrlCHandler(int signal){
		fprintf(stderr, "\nCtrl-C in OSS\n");
		fprintf(stderr, "Cleaning up....\n");
		// call cleanup to terminate and clean up
		cleanUp();
	}
 //------clean up
void cleanUp(){
	// kill processes
	signal(SIGINT, SIG_IGN);
 }