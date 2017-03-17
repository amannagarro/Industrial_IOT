/* xsh_trial.c - xsh_trial*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_trial - Trial
 *------------------------------------------------------------------------
 */
shellcmd xsh_trial(int nargs, char *args[]) {
	if(nargs==1){
		kprintf("trials 1 parameter bey\n");	
	}
	if(nargs==2){
		kprintf("trials 2 parameter bey %s\n",args[1]);	
	}	
}
