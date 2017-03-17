/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	uint32 i;
	
	/* Run the Xinu shell */
	int32 data;
	uid32 slot;
	recvclr();
	kprintf("main starts \n");
	
	resume(create(udp_edge_recv, NETSTK, 20, "udp_edge_receiver", 0, NULL));
	
	resume(create(temp_send, NETSTK, 20, "mqtt_sender", 0, NULL));	
	uint16 local_port = 1000;
	uint16 remote_port = 6666;
	uint32 remote_ip = 3232236037;
	slot = udp_register(remote_ip,remote_port,local_port);
	while(1){
		data = (int32)getc(TMP_SENSOR);
		kprintf("data recvd from temp sensor %d\n",data);
		char d[] = {data};
		kprintf(" %d\n",data);
		udp_send(slot,d,2);
		sleep(10000);			
	}

	//resume(create(temp_send, NETSTK, 20, "temp_send", 0, NULL));
	//resume(create(led_recv, NETSTK, 20, "led_recv", 0, NULL));


	//while(1)
	//{
		//i = getc(TMP_SENSOR);
		//kprintf("temp is %d\n",i);

		///i=getc(OBJ_SENSOR);
		//kprintf("prox is %d\n",i);
	//}
	return OK;
    
}
