#include<xinu.h>

devcall analoggetc(
      struct dentry  *devptr         		/* DEV */
    )

{
	uint32 i;
	SET_ENABLE;
	sleep(1);
	i = analog_read(devptr);
	SET_DISABLE;
	return i;
}
