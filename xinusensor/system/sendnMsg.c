#include<xinu.h>

/*---------------------------------------------------
 *  sendMsgs - Send a messages to multiple processes
 *---------------------------------------------------
 */

uint32 sendnMsg(
	uint32 pid_count,
	pid32* pids,
	umsg32 msg)
{
	uint32 count = 0;
	uint32 i;
	intmask	mask;

	mask = disable();
	for(i=0; i<pid_count; i++)
	{
		if(sendMsg(pids[i],msg) != SYSERR)	/* Increase count of messages successfully sent */
			count = count + 1;
	}
	restore(mask);
	return count;
}
