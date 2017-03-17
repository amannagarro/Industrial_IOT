/* xsh_updates_temp.c - xsh_updates_temp*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_updates_temp - Temperature regular updates
 *------------------------------------------------------------------------
 */
shellcmd xsh_updates_temp(int nargs, char *args[]) {

uint32 sleeptime,remote_ip;
uint16 remote_port;

	if(nargs==4){
		kprintf("parameter 1  bey %s\n",args[1]);	
		kprintf("parameter 2  bey %s\n",args[2]);	
		kprintf("parameter 3  bey %s\n",args[3]);	
		sleeptime = atoi(args[1]);
		remote_ip = atoi(args[2]);
		remote_port = atoi(args[3]);
		kprintf("so sleeptime is %s\n",sleeptime);
		kprintf("so remoteip is %s\n",remote_ip);
		kprintf("so remoteport is %s\n",remote_port);
		
		resume(create(regular_updates, NETSTK, 20, "regular_temp_updates", 3, sleeptime,remote_ip,remote_port));
		return 1;
		
	
	}
	else{
		kprintf(" give time interval,remote ip,remote port\n");	
		return 0;
	}	
}
