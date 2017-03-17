if(strcmp(devptr->dvname,"LED_RED")==0)
	led_write(1<<28,data);
if(strcmp(devptr->dvname,"LED_GREEN")==0)
	led_write(1<<29,data);
