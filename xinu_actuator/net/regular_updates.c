/* regular_updates.c */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

process regular_updates(uint32 sleeptime,uint32 remote_ip,uint16 remote_port){
	kprintf("regular updates after every %d seconds\n",sleeptime);
	uid32 slot;
	uint32 len;
	pid32 i;
	struct	tempupdates *tempupdateptr;

	for (i = 0; i < NPROCESSLIMIT; i++) {
		tempupdateptr = &tempupdatetab[i];
		if((tempupdateptr->remote_ip==remote_ip)&&(tempupdateptr->remote_port==remote_port)){
			kill(i);
			tempupdateptr->avail=TRUE;
			tempupdateptr->remote_ip = 0;
			tempupdateptr->remote_port = 0;
			tempupdateptr->slot = 20;
			break;
		}		
	}
	uint16 local_port = 1000;
	slot = udp_register(remote_ip,remote_port,local_port);

	tempupdateptr = &tempupdatetab[currpid];
	tempupdateptr->avail=FALSE;
	tempupdateptr->remote_ip = remote_ip;
	tempupdateptr->remote_port = remote_port;
	tempupdateptr->slot = slot;	

	while(1){
		data = (int32)getc(OBJ_SENSOR);
		kprintf("data recvd from obj sensor %d\n",data);
		char d[] = {data};
		kprintf(" %d\n",data);
		udp_send(slot,d,1);
		sleep(sleeptime);			
	}
}
