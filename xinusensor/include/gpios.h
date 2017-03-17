#define GPIO1_ADDR                     0x4804C000  
#define BBBIO_GPIO_OE                0x134
#define BBBIO_GPIO_DATAIN             0x138
#define BBBIO_GPIO_DATAOUT             0x13C
#define BBBIO_GPIO_CLEARDATAOUT        0x190
#define BBBIO_GPIO_SETDATAOUT        0x194			

#define SETDATAON(n) (*((unsigned int *)((void *)GPIO1_ADDR+BBBIO_GPIO_SETDATAOUT)) |= (n)) //sets set GPIO data(pin) out to 1

#define SETDATAOFF(n) (*((unsigned int *)((void *)GPIO1_ADDR+BBBIO_GPIO_CLEARDATAOUT)) |= (n)) //sets clear GPIO data(pin) out to 1

#define READ_DATA(n)    (*((unsigned int *)((void *)GPIO1_ADDR+BBBIO_GPIO_DATAIN)) &= (n))

#define SET_OE_OUT(n)  (*((unsigned int *)(((void *)GPIO1_ADDR) + BBBIO_GPIO_OE)) &= ~(n))

#define SET_OE_IN(n)  (*((unsigned int *)(((void *)GPIO1_ADDR) + BBBIO_GPIO_OE)) |= (n))

/*struct ledcblk{
	uint32 pinnum;	 //Pin number on which led is connected 
};

extern struct ledcblk ledtab[];*/
