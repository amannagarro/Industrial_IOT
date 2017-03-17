/* sendMsg.c - send */

#include <xinu.h>

/*------------------------------------------------------------------
 *  sendMsg - Pass message to process and make it ready if waiting
 *------------------------------------------------------------------
 */
syscall	sendMsg(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

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
	prptr->qtail = (prptr->qtail+1)%MAXQSIZE;
	prptr->msgq[prptr->qtail] = msg;		/* Deliver message */
	prptr->qcount = prptr->qcount+1;	/* Increase number of messages in queue	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
