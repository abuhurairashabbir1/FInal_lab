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
	msgrcv(queueid, mymsg, sizeof(mymsg_t), (long)atol(argv[1]), 0);
	printf ("Message read is %s\n", mymsg->mtext);
}


