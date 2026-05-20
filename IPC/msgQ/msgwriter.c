#include "msgqueue.h"

int main(int argc, char *argv[])
{
	int queueid;
	mymsg_t *mymsg;
	key_t mykey;
	if ((mykey = ftok(".", 5)) == -1)
	{
		perror("ftok failed");
		return 5;
	}
	queueid = msgget(mykey, PERM | IPC_CREAT);
   	if (queueid == -1) 
	{
		perror ("Unable to get msg queue");
      		return 1;
	}
	if ((mymsg = (mymsg_t *)malloc(sizeof(mymsg_t))) == NULL)
	{
		perror ("Unable to allocate memory");
      		return 1;
	}

	sprintf (mymsg->mtext, "This message was written by %ld\n",(long)getpid());
	mymsg->mtype = atoi(argv[1]);	
	if (msgsnd(queueid, mymsg, sizeof(mymsg_t), 0) == -1) 
	{
		perror ("Unable to send msg");
      		return 1;
	}	
}


