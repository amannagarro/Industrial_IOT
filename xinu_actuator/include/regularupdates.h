#ifndef NPROCESSLIMIT
#define	NPROCESSLIMIT	65536		
#endif


struct tempupdates {		/*Array for the topics subscribed to		*/
	
	uint32 remote_ip;
	uint16 remote_port;
	bool8 avail;
	uid32 slot;
};

extern	struct tempupdates tempupdatetab[];
