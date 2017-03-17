/* sendMsgs.c - send */

#include <xinu.h>

/*---------------------------------------------------
 *  sendMsgs - Send muliple messages to the process
 *---------------------------------------------------
 */
uint32	sendMsgs(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32*	msgs,		/* messages */
	  uint32	msg_count	/* number of messages to send */
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	uint32 index = 0;		/* Index to access the messages */
	umsg32 msg;			/* Store messsage to send in local variable and then send */
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->qcount == MAXQSIZE) {
		restore(mask);
		return SYSERR;
	}

	/* Deliver message unitl all messages are sent or until it reaches the max limit of the receiving process's buffer */
	while((prptr->qcount != MAXQSIZE) && (msg_count!=0))
	{
		prptr->qtail = (prptr->qtail+1)%MAXQSIZE;
		msg = msgs[index];
		index = index+1;
		prptr->msgq[prptr->qtail] = msg;		/* Deliver message		*/
		prptr->qcount = prptr->qcount+1;	/* Increase number of messages in queue	*/
		msg_count = msg_count - 1;
	}

	/* If recipient waiting or in timed-wait make it ready */
	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return (index);
}
