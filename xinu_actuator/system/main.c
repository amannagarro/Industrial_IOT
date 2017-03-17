
/*  main.c  - main */

#include <xinu.h>

process	main(void)
{

	/* Run the Xinu shell */

	recvclr();
	kprintf("main\n");
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
/*
	kprintf("main starts \n");
	
	resume(create(udp_edge_recv, NETSTK, 20, "udp_edge_receiver", 0, NULL));
	resume(create(temp_send, NETSTK, 20, "temp_send", 0, NULL));
*/
}
