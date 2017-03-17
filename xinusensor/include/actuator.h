if(strcmp(devptr->dvname,"LED_RED")==0)
actuator_write(1<<28,data);
if(strcmp(devptr->dvname,"LED_GREEN")==0)
actuator_write(1<<28,data);
