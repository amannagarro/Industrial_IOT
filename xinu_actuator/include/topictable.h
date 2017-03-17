#ifndef NTOPICS
#define	NTOPICS		256
#endif

#define MAXSUB	8

#define	isbadtopicid(x)	( ((topic16)(x) < 0) || \
			  ((topic16)(x) >= 0xffff) )

struct topicent {		/* Entry in the topic table		*/
	pid32	subscribers[MAXSUB];
	int32	(*handlerArray[MAXSUB])(topic16 topic,uint32 data);
	int32	thead;		/* head for subscriber and handlerArray*/
	int32   ttail;		/* tail for subscriber and handlerArray*/
	int32   topiccount;	/* count of subscribers in the queue		*/
	int16	group[MAXSUB];	/* group that the subscriber belongs to */
};

extern	struct topicent	topictable[];
