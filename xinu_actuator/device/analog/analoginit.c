#include<xinu.h>

devcall analoginit(struct dentry *devptr) 
{
	uint32 i;
	
	SET_CM_WKUP_CONTROL_CLKCTRL;
	SET_CM_WKUP_CLKSTCTRL;
	SET_CM_L3_AON_CLKSTCTRL;
	SET_CM_WKUP_ADC_TSC_CLKCTRL;

	while(*((unsigned int *)CM_WKUP_CLKSTCTRL) & (0x01<<2) != 0x00 );
	while(*((unsigned int *)CM_WKUP_CONTROL_CLKCTRL) & (0x03<<16) != 0x00 );
	while(*((unsigned int *)CM_L3_AON_CLKSTCTRL) & (0x01<<3) != 0x00 );		
	while(*((unsigned int *)CM_WKUP_ADC_TSC_CLKCTRL) & (0x03<<16) != 0x00 );

	SET_STEPCONFIG_WRITE_PROTECT;
	 #include<analogSensorInitialize.h>
	/*if(strcmp(devptr->dvname,"TMP_SENSOR")==0)
		(*((unsigned int *)STEP_CONFIG1) |= (3<<19));*/
	SET_CONFIG;
	SET_ADC;
	return OK;
}
