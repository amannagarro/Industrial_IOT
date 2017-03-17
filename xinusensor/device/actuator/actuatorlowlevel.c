#include<xinu.h>

void actuator_write(uint32 pin,uint32 data)
{

	SET_OE_OUT(pin);

	if(data==1)
    	{
		kprintf("ON\n");
        	SETDATAON(pin);
    	}
   	 else
    	{
		kprintf("OFF\n");
        	SETDATAOFF(pin);
    	}

	return OK;
}
