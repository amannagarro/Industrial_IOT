/* ledudp.c - led_recv */
#include <xinu.h>
#include <stdio.h>
#include <string.h>
process led_recv(uint32 topic_id,uint32 remote_ip,uint16 remote_port){
	//kprintf("received topicid %d remoteip %d remoteport %d",topic_id,remote_ip,remote_port);
	// get subscribedto table entry	 using topicid
	struct 	subscribedto	*subtoptr;	
	subtoptr = &substable[topic_id];

	//update process id in table entry
	subtoptr->processid = currpid;

	//get local port from entry
	uint16 local_port;
	local_port = subtoptr->port;
	//kprintf("led listener1 started on port %d \n ",local_port);
	//register new slot
	uid32 slot;
	uint32 i;
	while(1){
		slot = udp_register(0,0,local_port);
		if(slot!=-1){
			break;
		}
	}
				
	kprintf("led listener started on port %d \n ",local_port);	
	kprintf("led listener registered on slot %d \n ",slot);
	
	while(1){
	char data2[10];	
	uint32 len;	
	len = udp_recv(slot,data2,50,2000);
	if(len==TIMEOUT){
		//kprintf("timeout %d th time",i);
		continue;
	}
	else if(len==SYSERR){
		//kprintf("syserr %d th time",i);
		continue;
	}
		else{	
			//kprintf("\n",data2);
			kprintf("led remote input data %s \n",data2);
			uint32 d = 5;
			d = atoi(data2);
			kprintf("led remote input data %d \n",d);
			if(d==1){
				actuatoron(LED_RED);
				//putc();
			}
			
			if(d==0){
				actuatoroff(LED_RED);
			}
			continue;
		}	
	}
	return OK;
}
