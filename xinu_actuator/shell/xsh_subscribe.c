/* xsh_subscribe.c - xsh_subscribe*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_subscribe - Subscribe to a topic
 *------------------------------------------------------------------------
 */
shellcmd xsh_subscribe(int nargs, char *args[]) {
	uint32 topic_id,remote_ip,i;
	uint16 port,remote_port;
	uid32 slot;
	struct 	subscribedto	*subtoptr;
	if(nargs==5){
		//kprintf("parameter 1 is %s\n",args[1]);
		//kprintf("parameter 2 is %s\n",args[2]);

		topic_id = atoi(args[1]);
		port = atoi(args[2]);
		remote_ip = atoi(args[3]);
		remote_port = atoi(args[4]);

		kprintf("topic id is %d \n",topic_id);
		kprintf("port is %d \n",port);
		//kprintf("remote_ip is %d \n",remote_ip);
		//kprintf("remote_port is %d \n",remote_port);
		for (i = 0; i < NSUBSCRIBEDTO; i++) {
			subtoptr = &substable[i];
			//kprintf("local port is %d\n",subtoptr->port);
			
			if((subtoptr->port)==port){
				kprintf("local port already in use \n");
				return 0;
			}
	 		
		}
		//subscribedto table
		subtoptr = &substable[topic_id];
		if(subtoptr->avail==TRUE){
			subtoptr->port = port;
			subtoptr->avail=FALSE;

		}
		else{
			kprintf("topic already subscribed \n");
			return 0;
		}


		// register for udp slot
		slot = udp_register(remote_ip,remote_port,port);

		//buffer to send
		char d[] = {topic_id};

		//send data udp
		udp_send(slot,d,1);
		
		kprintf("subscribed to %d\n",topic_id);
		//slot release
		udp_release(slot);
		resume(create(led_recv, NETSTK, 20, "led_receiver", 3, topic_id,remote_ip,remote_port));
		return 1;					
	}
	else{
		kprintf("needs 4 values-topic,local,remoteip,remoteport \n");
		return 0;
	}	
}
