#include <xinu.h>

syscall subscribe(
		topic16 topic, 
		void (*handler)(topic16 topic, uint32 data))
{
	
	intmask	mask;			/* Saved interrupt mask		*/
	struct	topicent *topicptr;		/* Ptr to topic table entry	*/
	struct	procent	*prptr;
	pid32 subscriber;
	int32 index;
	int16 topicnum;
	int16 group;

	mask = disable();
	if (isbadtopicid(topic)) {
		restore(mask);
		return SYSERR;
	}
	kprintf("passed one\n");
	group = (topic >> 8);
	topicnum = (topic & 0xFF);
	subscriber = getpid();
	prptr = &proctab[subscriber];

	topicptr = &topictable[topicnum];
	if (topicptr->topiccount == MAXSUB) {
		restore(mask);
		return SYSERR;
	}
	kprintf("passed two\n");
	for(index=topicptr->thead;index<=topicptr->ttail;index++)			/* Check if subscriber has already suscribed */
	{
		if(topicptr->subscribers[index]==subscriber)
		{
			restore(mask);
			return SYSERR;
		}
	}
	kprintf("passed three\n");
	topicptr->ttail = topicptr->ttail + 1;
	topicptr->subscribers[topicptr->ttail] = subscriber;
	topicptr->handlerArray[topicptr->ttail] = handler;
	topicptr->group[topicptr->ttail] = group;
	kprintf("subscriber before %d\n",topicptr->topiccount);
	topicptr->topiccount = topicptr->topiccount + 1;
	kprintf("subscriber after %d %d\n",topicptr->topiccount,topicnum);
	prptr->sub_topics[prptr->ntopic] = topic;	/* Add topic subscribed to in the process table*/
	prptr->ntopic = prptr->ntopic + 1;
	restore(mask);		/* Restore interrupts */
	return OK;

}
