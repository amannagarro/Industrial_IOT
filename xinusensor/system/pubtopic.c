#include <xinu.h>
void enqueueTopic(topic16 topic,uint32 data)
{

	struct pubtopic *link = (struct pubtopic*) getmem(sizeof(struct pubtopic));
	struct pubtopic *curr;
	link->topicid = topic;
	link->data = data;
	curr = head1;
	if(head1==NULL)
	{
		head1 = link;
		link->next = NULL;
		rem_count = rem_count + 1;
	}
	else
	{
		while(curr->next!=NULL)
		{
			curr = curr->next;
		}
		curr->next = link;
		link->next = NULL;
		rem_count = rem_count +  1;	
	}
	kprintf("enqueued\n");	
}
		
struct pubtopic* dequeueTopic()
{
	struct pubtopic *curr;
	curr = head1;
	head1 = curr->next;
	kprintf("dequeued\n");
	return curr;
	
}	 
