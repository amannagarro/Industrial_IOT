/* xsh_updates_tempoff.c - xsh_updates_tempoff*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_updates_temp - Temperature regular updates
 *------------------------------------------------------------------------
 */
shellcmd xsh_updates_tempoff(int nargs, char *args[]) {
	uint32 remote_ip;
	uint16 remote_port;
	pid32 i;
	if(nargs==3){
		kprintf("parameter 1  bey %s\n",args[1]);	
		kprintf("parameter 2  bey %s\n",args[2]);		
		remote_ip = atoi(args[1]);
		remote_port = atoi(args[2]);
		struct	tempupdates *tempupdateptr;
		for (i = 0; i < NPROCESSLIMIT; i++) {
			tempupdateptr = &tempupdatetab[i];
			if((tempupdateptr->remote_ip==remote_ip)&&(tempupdateptr->remote_port==remote_port)){
				kill(i);
				tempupdateptr->avail=TRUE;
				tempupdateptr->remote_ip = 0;
				tempupdateptr->remote_port = 0;
				tempupdateptr->slot = 20;
				return 1;
			}
		}
	}
	else{
		kprintf(" Please enter remote ip,remote port\n");	
		return 0;
	}
}
