/* xsh_unsubscribe.c - xsh_unsubscribe*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_unsubscribe - Unsubscribe to a topic
 *------------------------------------------------------------------------
 */
shellcmd xsh_unsubscribe(int nargs, char *args[]) {
	uint32 topic_id,remote_ip;
	uid32 slot,slot2;
	pid32 processid;
	uint16 remote_port,port;
	port = 65530;
	if(nargs==4){
		//kprintf("parameter 1 is %s\n",args[1]);
		//kprintf("parameter 2 is %s\n",args[2]);
		//kprintf("parameter 3 is %s\n",args[3]);
		topic_id = atoi(args[1]);
		remote_ip = atoi(args[2]);
		remote_port = atoi(args[3]);
		kprintf("topic id is %d \n",topic_id);
		kprintf("remote ip is %d \n",remote_ip);
		kprintf("remote port is %d \n",remote_port);

		// get subscribedto table entry	 using topicid
		struct 	subscribedto	*subtoptr;	
		subtoptr = &substable[topic_id];

		// register for udp slot
		slot2 = udp_register(remote_ip,remote_port,port);

		//buffer to send
		char d[] = {topic_id};

		//send data udp
		udp_send(slot2,d,1);
		
		kprintf("unsubscribed to %d \n",topic_id);
		//slot release
		udp_release(slot2);

		slot = subtoptr->avail;
		udp_release(slot);
		processid = subtoptr->processid;
		kill(processid);
		subtoptr->avail=TRUE;
		subtoptr->port = 70000;
		subtoptr->slot = 20;
		
	}
	else{
		kprintf(" Invalid parameters\n");
	}	
}
