/* devudp.c - udp_edge_recv, udp_edge_send */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

process udp_edge_send(char* data2,uint32 length){
	did32 s;
	s = atoi(data2);
	int32 data;
	kprintf("to process is %d \n",s);
	data = (int32)getc(s);
	kprintf("data recvd %d\n",data);	
	//data2 = data;
	uid32 slot;
	uint32 i,len;
	uint32 remote_ip = 3232236039;
	uint16 remote_port = 3333;
	uint16 local_port = 48570;
	slot = udp_register(remote_ip,remote_port,local_port);
	//char data[] = {'d','e','a','d'};
	char d[] = {data};
	kprintf(" length of temp/proximity is %d\n",sizeof(data)/sizeof(char));
	
	udp_send(slot,d,sizeof(data)/sizeof(char));
	udp_release(slot);
	return OK;
}
process udp_edge_recv(void){
	
	kprintf("udp server has started \n");
	uint16 local_port = 48569;
	uid32 slot;
	uint32 i,len;	
	char data2[50];

	slot = udp_register(0,0,local_port);

	while(1){		
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
			kprintf("length is %d \n",len);
			kprintf("data is %s \n",data2);
			resume(create(udp_edge_send, NETSTK, 20, "udp_edge_send", 2, data2,len));	
			continue;
		}	
	}
}

