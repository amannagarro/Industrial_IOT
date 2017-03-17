

struct	pubtopic{		/* One per process plus two per list	*/
	topic16	topicid;		/* Topic ID	*/
	uint32	data;			/* Data published for corresponding topic */
	struct pubtopic *next;
};

struct pubtopic* head1;

extern struct pubtopic pubtable[];
extern int16 rem_count;
