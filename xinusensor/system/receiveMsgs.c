/* receiveMsg.c - receive */

#include <xinu.h>

/*----------------------------------------------------
 *  receive  -  Wait for messages to arrive in queue
 *----------------------------------------------------
 */
syscall	receiveMsgs(umsg32* msgs,uint32 msg_count)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/
	int32 i;

	mask = disable();
	prptr = &proctab[currpid];
	while(prptr->qcount < msg_count) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until messages arrive	*/
	}
	for(i=0; i<msg_count; i++)
	{
		msg = prptr->msgq[prptr->qhead];		/* Retrieve message		*/
		prptr->qhead=(prptr->qhead+1)%MAXQSIZE;
		msgs[i] = msg;
		prptr->qcount=prptr->qcount-1;		/* Decrease count of messages in queue  */
	}
	restore(mask);
	return OK;
}
