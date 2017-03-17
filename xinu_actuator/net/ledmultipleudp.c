/* ledmultipleudp.c - led_recv */
#include <xinu.h>
#include <stdio.h>
#include <string.h>
process led_multiple_recv(void){
	uint16 local_port = 48569;
	//register new slot
	uid32 slot;
	slot = udp_register(0,0,local_port);			
	kprintf("led listener2 started on port %d \n ",local_port);	
	kprintf("led listener3 registered on slot %d \n ",slot);
	int32 a[40]={0};
	kprintf("a[0] %d \n",a[0]);
	kprintf("a[1] %d \n",a[1]);
	kprintf("a[2] %d \n",a[2]);
	kprintf("a[28] %d \n",a[28]);
	kprintf("a[29] %d \n",a[29]);
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
			uint32 d;
			d = atoi(data2);
			if(a[d]==0){
				actuatoron(d);
				a[d]=1;
				continue;
			}
			if(a[d]==1){
				actuatoroff(d);
				a[d]=0;
				continue;
			}					
		}

	}
	return OK;
}
