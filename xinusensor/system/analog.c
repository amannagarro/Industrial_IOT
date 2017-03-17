#include<xinu.h>

uint32 analog_read(struct dentry  *devptr)
{
	uint32 i,temp_degrees;
	float milliVolts;
	/*SET_ENABLE;
	i = getc(descrp);
	SET_DISABLE;*/
	i = READ_FIFO;
	milliVolts = (i*1.8/4095)*1000;
	 #include<analogSensor.h>
	/* Convert to degree celsius/fahr */
	//temp_degrees = (uint32)(milliVolts-500)/10;
	return temp_degrees;
}
