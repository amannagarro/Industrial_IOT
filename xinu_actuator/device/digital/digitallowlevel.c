#include<xinu.h>

uint32  sensor_read(uint32 pin)
{

    uint32 i;
    kprintf("reading\n");
    SET_OE_IN(pin);
    i = READ_DATA(pin);
    kprintf("read\n");
    return i;

}
