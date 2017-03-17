#include <xinu.h>

syscall publish(
		topic16 topic, 
		uint32 data
		)
{
	
	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();
	if (isbadtopicid(topic)) {
		restore(mask);
		return SYSERR;
	}
	enqueueTopic(topic,data);
	kprintf("enqueueing\n");
	restore(mask);		/* Restore interrupts */
	return OK;
}
