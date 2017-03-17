/* proximityudp.c - proximity_send */

#include <xinu.h>
#include <stdio.h>
#include <string.h>


process proximity_send(void){
	kprintf("proximity server started\n");
	int32 data;
	uint32 remote_ip = 3232236037;
	uint16 remote_port = 48569;
	uint16 local_port = 48572;	
	uid32 slot;	
	slot = udp_register(remote_ip,remote_port,local_port);
	while(1){
		data = (int32)getc(OBJ_SENSOR);
		if(data==1){
			data=2;
			kprintf("proximity sent data %d\n",data);
			char d[] = {'2',',','0'};
			//kprintf(" %d\n",data);
			udp_send(slot,d,3);
			udp_release(slot);
			kill(currpid);
			break;
		}
	}
	return OK;
}
