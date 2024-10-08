/* #include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
void main(){
key_t j;
j=ftok(".","s");
printf("%d\n",j);
int value =shmget(j,1818,IPC_CREAT|0666);
printf("%d\n",value);
int *shat=shmat(value,0,0);
char data[30];
printf("enter the data\n");
scanf("%s",data);
strcpy(shat,data);
printf("%s\n",(char*)shat);
int dtach=shmdt(shat);
printf("%d\n",dtach);
int shctl=shmctl(value,IPC_RMID,NULL);
printf("%d\n",shctl);
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#define SEGSIZE 100
int main(int argc, char *argv[ ])
{
int shmid,cntr; key_t key;
char *segptr;
char buff[]="Hello";
key=ftok(".",'s');
if((shmid=shmget(key, SEGSIZE, IPC_CREAT | IPC_EXCL | 0666))== -1)
{
if((shmid=shmget(key,SEGSIZE,0))==-1)
{
perror("shmget");
exit(1);
}
}
else
{
printf("Creating a new shared memory seg \n");
printf("SHMID:%d",shmid);
}
system("ipcs –m");
if((segptr=(char*)shmat(shmid,0,0))==(char*)-1)
{
perror("shmat");
exit(1);
}
printf("Writing data to shared memory…\n");
strcpy(segptr,buff);
printf("DONE\n");
printf("Reading data from shared memory…\n");
printf("DATA:-%s\n",segptr);
printf("DONE\n");
printf("Detaching\n");
shmdt(segptr);
printf("DONE\n");
printf("Removing shared memory Segment…\n");
if(shmctl(shmid,IPC_RMID,0)== -1)
printf("Can‟t Remove Shared memory Segment…\n");
else
printf("Removed Successfully");
}
