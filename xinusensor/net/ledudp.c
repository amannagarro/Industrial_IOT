/* ledudp.c - led_recv */
#include <xinu.h>
#include <stdio.h>
#include <string.h>
process led_recv(void){
	kprintf("led listener started\n");
	uint16 local_port = 48573;
	uid32 slot;
	uint32 i;	
	kprintf("in led receive");
	slot = udp_register(0,0,local_port);

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
