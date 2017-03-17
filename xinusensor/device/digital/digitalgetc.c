#include<xinu.h>

devcall    digitalgetc(
      struct dentry    *devptr            		/* DEV */
    )
{
    uint32 i;
    //i=4;
    /*Insert header file for object sensor here*/
   #include<digitalSensor.h>
    /* Genereate code from DDL */
    /*if(strcmp(devptr->dvname,"OBJ_SENSOR")==0)
    	i = sensor_read(1<<28);*/
kprintf("%d is the value from proximity\n",i);
    if(i!=0){
	i = 1;
	}
    return (devcall) i;
}


