#include <xinu.h>

syscall unsubscribe(
		topic16 topic
		  )
{
	
	intmask	mask;			/* Saved interrupt mask		*/
	struct	topicent *topicptr;		/* Ptr to topic table entry	*/
	struct	procent	*prptr;
	pid32 unsubscriber;
	int32 i,index,count,j;
	unsubscriber = getpid();
	int16 topicnum;

	mask = disable();
	if (isbadtopicid(topic)) {
		restore(mask);
		return SYSERR;
	}
	
	topicnum = (topic & 0xFF);

	topicptr = &topictable[topicnum];
	prptr = &proctab[unsubscriber];	

	if (topicptr->topiccount==0) {
		restore(mask);
		return SYSERR;
	}

	count = topicptr->topiccount;
	index = topicptr->thead;

	for(i=1;i<=count;i++)
	{
		if(topicptr->subscribers[index]==unsubscriber)
		{
			if(index==topicptr->ttail)
			{
				topicptr->ttail = topicptr->ttail - 1;
				topicptr->topiccount = topicptr->topiccount -1;
				restore(mask);		/* Restore interrupts */
				return OK;
			}
			else
			{
				j=index;
				while(j!=topicptr->ttail)
				{
					topicptr->subscribers[j] = topicptr->subscribers[j+1];
					topicptr->handlerArray[j] = topicptr->handlerArray[j+1];
					topicptr->group[j] = topicptr->group[j+1];
					j = j+1;
				}

				topicptr->ttail = topicptr->ttail - 1;
				topicptr->topiccount = topicptr->topiccount -1;
				restore(mask);		/* Restore interrupts */
				return OK;
			}
		}
		index = index + 1;
	}
	for(i=0;i<prptr->ntopic;i++)
	{
		if(prptr->sub_topics[i]==topic)
		{
			prptr->sub_topics[i] = prptr->sub_topics[i+1];
			prptr->ntopic = prptr->ntopic - 1;
		}
	}
	if(count==topicptr->topiccount)
	{
		restore(mask);		/* Restore interrupts */
		return SYSERR;
	}
	restore(mask);
	return OK;

}
