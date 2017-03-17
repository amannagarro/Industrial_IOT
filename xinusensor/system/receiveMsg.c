/* receiveMsg.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------------------------------
 *  receiveMsg  -  Wait for a message to arrive in the queue and return the message to the caller
 *------------------------------------------------------------------------------------------------
 */
umsg32	receiveMsg(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->qcount == 0) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->msgq[prptr->qhead];		/* Retrieve message	*/
	prptr->qhead=(prptr->qhead+1)%MAXQSIZE;
	prptr->qcount=prptr->qcount-1;		/* Decrease count of messages in queue  */
	restore(mask);
	return msg;
}
