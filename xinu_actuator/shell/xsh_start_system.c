/* xsh_start_system.c - xsh_updates_tempoff*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_updates_temp - Temperature regular updates
 *------------------------------------------------------------------------
 */
shellcmd xsh_start_system(int nargs, char *args[]) {
uint32 a;

	if(nargs==2){
		kprintf("parameter 1  bey %s\n",args[1]);	
	
		a = atoi(args[1]);				
		switch(a){
		case 1://BBB for temp sensor and priximity
			kprintf("Starting process for Publishers i.e. Sensors\n");
			resume(create(udp_edge_recv, NETSTK, 20, "udp_edge_receiver", 0, NULL));
			resume(create(temp_send, NETSTK, 20, "temp_send", 0, NULL));
			return 1;
		

		case 2://BBB for actuator in MQTT i.e LED
			actuatoroff(LED_RED);
			sleep(2);
			actuatoron(LED_RED);
			sleep(3);
			actuatoroff(LED_RED);
			sleep(3);
			kprintf("Actuator ready for use in MQTT.\n");
			kprintf("To subscribe to topics use the command subscribe\n");
			return 1;
		

		case 3://BBB for actuator in UI i.e. LED 3 nos
			kprintf("Actuators ready for use\n");
			resume(create(led_multiple_recv, NETSTK, 20, "led_multiple_recv", 0, NULL));
			return 1;
		
	
		default://Invalid Parameter
			kprintf("Invalid Parameter\n");
			return 0;
		}		

	
	}
	else{
		kprintf(" Input valid System Start parameters\n");	
		return 0;
	}	
	
}
