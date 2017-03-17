#include<xinu.h>

devcall    actuatorputc(
      struct dentry    *devptr,    /* Entry in device switch table    */
      char    ch            /* Char */
    )
{
    uint32 data;
    data = ch - '0';

    /* Include header file for led here */
    #include<actuator.h>
    /* Generate from DDL	
    if(strcmp(devptr->dvname,"LED_RED")==0)
	actuator_write(1<<28,data);
    if(strcmp(devptr->dvname,"LED_GREEN")==0)
	actuator_write(1<<29,data);*/
	
    return OK;
}

