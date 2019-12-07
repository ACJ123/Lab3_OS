#include  <stdio.h>
#include  <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include  <sys/types.h>
#include  <sys/shm.h>
#include  <sys/ipc.h>


void  memoryHandler(int []);

int  main(int  argc, char *argv[])
{
     int    memoryID;
     int    *memoryPTR;
     pid_t  pid;
     int    status;

     if (argc != 11) {
          printf("Use: %s #1 #2 #3 #4 #5 #6 #7 #8 #9 #10\n", argv[0]);
          exit(1);
     }

     memoryID = shmget(IPC_PRIVATE, 10*sizeof(int), IPC_CREAT | 0666);
     if (memoryID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of ten integers...\n");

     memoryPTR = (int *) shmat(memoryID, NULL, 0);
     if (*memoryPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

     memoryPTR[0] = atoi(argv[1]);
     memoryPTR[1] = atoi(argv[2]);
     memoryPTR[2] = atoi(argv[3]);
     memoryPTR[3] = atoi(argv[4]);
     memoryPTR[4] = atoi(argv[5]);
     memoryPTR[5] = atoi(argv[6]);
     memoryPTR[6] = atoi(argv[7]);
     memoryPTR[7] = atoi(argv[8]);
     memoryPTR[8] = atoi(argv[9]);
     memoryPTR[9] = atoi(argv[10]);
     printf("Server has filled %d %d %d %d %d %d %d %d %d %d in shared memory...\n",
            memoryPTR[0], memoryPTR[1], memoryPTR[2], memoryPTR[3], memoryPTR[4], memoryPTR[5], memoryPTR[6], memoryPTR[7], memoryPTR[8], memoryPTR[9]);

     printf("Server is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          memoryHandler(memoryPTR);
          exit(0);
     }
     else{
           wait(&status);
           printf("Server has detected the completion of its child...\n");
           printf("This is the Parent process!\n");
           printf("Server found %d %d %d %d %d %d %d %d %d %d in shared memory...\n",
            memoryPTR[0], memoryPTR[1], memoryPTR[2], memoryPTR[3], memoryPTR[4], memoryPTR[5], memoryPTR[6], memoryPTR[7], memoryPTR[8], memoryPTR[9]);
           shmdt((void *) memoryPTR);
           printf("Server has detached its shared memory...\n");
           shmctl(memoryID, IPC_RMID, NULL);
           printf("Server has removed its shared memory...\n");
           printf("Server exits...\n");
           exit(0);
     }
}

void  memoryHandler(int  memorySpace[])
{
     printf("   handler process started\n");
     printf("   handler found %d %d %d %d %d %d %d %d %d %d in shared memory\n",
                memorySpace[0], memorySpace[1], memorySpace[2], memorySpace[3], memorySpace[4], memorySpace[5], memorySpace[6], memorySpace[7], memorySpace[8], memorySpace[9]);
     printf("   handler is about to exit\n");
}