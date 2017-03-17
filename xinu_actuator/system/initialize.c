/* initialize.c - nulluser, sysinit */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
local	process startup(void);	/* Process to finish startup tasks	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/
//struct	pubtopic pubtable[NTOPICS];
//struct  topicent topictable[NTOPICS];
struct subscribedto substable[NSUBSCRIBEDTO];
struct tempupdates tempupdatetab[NPROCESSLIMIT];

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/
int16	rem_count;		/*Countof the topics remaining to be published*/

/* Control sequence to reset the console colors and cusor positiion	*/

#define	CONSOLE_RESET	" \033[0m\033[2J\033[;H"

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */
/*process broker()
{
	int32 i,index,count;
	topic16 t;
	uint32 d;
	struct pubtopic *ptr;
	struct topicent *tptr;
	void (*funcptr)(topic16,uint32);
	int16 topicnum;
	int16 group;
	kprintf("broker called\n");
	while(1)
	{
	while(rem_count!=0)
	{
		ptr = dequeueTopic();
		t = ptr->topicid;
		kprintf("%d insdide rem\n",t);
		topicnum = (t & 0xFF);
		group = (t >> 8);
		d = ptr->data;
		kprintf("%d topic num\n",topicnum);
		tptr = &topictable[topicnum];
		index = tptr->thead;
		count = tptr->topiccount;
		kprintf("%d is count\n",tptr->ttail);
		if(count!=0)
		{
		if(group==0)
		{kprintf("if test\n");
		while(count!=0)
		{	
			kprintf("inside loop\n");
			funcptr = tptr->handlerArray[index];
			funcptr(t,d);
			index = index + 1;
			count = count - 1;
		}
		}
		else
		{kprintf("else test\n");
			for(i=tptr->thead;i<tptr->topiccount;i++)
			{
				if(tptr->group[i]==group)
				{
					funcptr = tptr->handlerArray[i];
					funcptr(t,d);
				}
			}
		}
		}
		rem_count = rem_count - 1;
		
	}
	}
}*/
void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */

	sysinit();
	kprintf("nulluser\n");
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();

	/* Initialize the network stack and start processes */

	 net_init(); 

	/* Create a process to finish startup and start main */

	resume(create((void *)startup, INITSTK, INITPRIO,
					"Startup process", 0, NULL));
	//resume(create(broker, 4096, 50, "broker", 0));

	
	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}

/*------------------------------------------------------------------------
 *
 * startup  -  Finish startup takss that cannot be run from the Null
 *		  process and then create and resumethe main process
 *
 *------------------------------------------------------------------------
 */
local process	startup(void)
{
	uint32	ipaddr;			/* Computer's IP address	*/
	char	str[128];		/* String used to format output	*/
kprintf("startup\n");

	/* Use DHCP to obtain an IP address and format it */

	ipaddr = getlocalip();
	if ((int32)ipaddr == SYSERR) {
		kprintf("Cannot obtain an IP address\n");
	} else {
		/* Print the IP in dotted decimal and hex */
		ipaddr = NetData.ipucast;
		sprintf(str, "%d.%d.%d.%d",
			(ipaddr>>24)&0xff, (ipaddr>>16)&0xff,
			(ipaddr>>8)&0xff,        ipaddr&0xff);
	
		kprintf("Obtained IP address  %s   (0x%08x)\n", str,
								ipaddr);
	}
	/* Create a process to execute function main() */

	resume(create((void *)main, INITSTK, 50,
					"Main process", 0, NULL));
	//resume(create(broker, 4096, 50, "broker", 0));
	/* Startup process exits at this point */

	return OK;
}


/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/
	struct 	subscribedto	*subtoptr;
	struct	topicent *tptr;	
	struct	tempupdates *tempupdateptr;

	kprintf(CONSOLE_RESET);
	kprintf("\n%s\n\n", VERSION);
kprintf("sysinit\n");
	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Initializing head and tail for published topics table - pubtable(topic.h)	*/
	rem_count = 0;
	
	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
	
	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize  topics */

	/*for (i = 0; i < NTOPICS; i++) {
		tptr = &topictable[i];
		tptr->thead = 0;
		tptr->ttail = -1;
		tptr->topiccount = 0;
	}*/
	
	/* Initialize  subscribedto table */

	for (i = 0; i < NSUBSCRIBEDTO; i++) {
		subtoptr = &substable[i];
		subtoptr->port = 0;
		subtoptr->avail = TRUE;
		subtoptr->slot = 20;
		subtoptr->processid = 65537;		
	}
	/* Initialize  tempupdates table */

	for (i = 0; i < NPROCESSLIMIT; i++) {
		tempupdateptr = &tempupdatetab[i];
		tempupdateptr->remote_ip = 0;
		tempupdateptr->remote_port = 0;
		tempupdateptr->slot = 20;
		tempupdateptr->avail = TRUE;		
	}
	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}
	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
