/* tempudp.c - temp_send */

#include <xinu.h>
#include <stdio.h>
#include <string.h>


process temp_send(void){
	kprintf("temp server started \n");
	uint32 threshold = 26;
	uint32 x = 0;	
	uint32 remote_ip = 3232236037;
	uint16 remote_port = 48569;
	uint16 local_port = 48571;
	uid32 slot;
	uint32 data;
	slot = udp_register(remote_ip,remote_port,local_port);
	while(1){
	
	data = (uint32)getc(TMP_SENSOR);
	kprintf("data is %d\n",data);
		if((data>=threshold)&&(x==0)){			
			char d[] = {'1',',','1'};
			//kprintf("data is %d\n",data);
			kprintf("temp data sent");
			udp_send(slot,d,3);
			
			resume(create(proximity_send, NETSTK, 20, "proximity_send", 0, NULL));
			x = 1;
		}
		if(data<threshold){
			kprintf("threshold dropped%d \n",data);
			x = 0;
		}
		//sleep(5);
	}
	udp_release(slot);
	return OK;
}

