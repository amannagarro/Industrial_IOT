#ifndef NSUBSCRIBEDTO
#define	NSUBSCRIBEDTO		256
#endif


struct subscribedto {		/*Array for the topics subscribed to		*/
	
	uint16 port;
	bool8 avail;
	pid32 processid;
	uid32 slot;
};

extern	struct subscribedto substable[];
