#include<xinu.h>

devcall analoginit(struct dentry *devptr) 
{
	
	SET_CM_WKUP_CONTROL_CLKCTRL;
	SET_CM_WKUP_CLKSTCTRL;
	SET_CM_L3_AON_CLKSTCTRL;
	SET_CM_WKUP_ADC_TSC_CLKCTRL;

	//HWREG(CM_WKUP_CONTROL_CLKCTRL) |= 0x02;                             //enbale wkup control clk
	//while(( HWREG(CM_WKUP_CONTROL_CLKCTRL) & 0x03 ) != 0x02 );          //wait 

	//HWREG(CM_WKUP_CLKSTCTRL) |= 0x02;                                   //enbale wkup st clk
	//while(( HWREG(CM_WKUP_CLKSTCTRL) & 0x03 ) != 0x02 );                //wait 

	//HWREG(CM_L3_AON_CLKSTCTRL) |= 0x02;                                 //enbale wkup st clk
	//while(( HWREG(CM_L3_AON_CLKSTCTRL) & 0x03 ) != 0x02 );              //wait

	//HWREG(CM_WKUP_ADC_TSC_CLKCTRL) |= 0x02;                             //enbale wkup st clk
	//while(( HWREG(CM_WKUP_ADC_TSC_CLKCTRL) & 0x03 ) != 0x02 );          //wait

	/*while(( HWREG(CM_WKUP_CONTROL_CLKCTRL) & (0x03<<16) ) != 0x00 );            //wait wkup control clk fully functional
	while(( HWREG(CM_L3_AON_CLKSTCTRL) & (0x01<<3) ) == 0x00 );                 //wait L3 AON gclk active
	while(( HWREG(CM_WKUP_L4WKUP_CLKCTRL) & (0x03<<16) ) != 0x00 );             //wait L4 WKUP CLK fully functional*/
	//while(( HWREG(CM_WKUP_CLKSTCTRL) & (0x01<<2) ) == 0x00 );                   //wait L4 WKUP GCLK active
	//while(( HWREG(CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL) & (0x01<<2) ) == 0x00 );    //wait L4 WKUP aon CLK active
	//while(( HWREG(CM_WKUP_CLKSTCTRL) & (0x01<<14) ) == 0x00 );                  //wait ADC fclk active*/

	while(*((unsigned int *)CM_WKUP_CLKSTCTRL) & (0x01<<2) != 0x00 );
	while(*((unsigned int *)CM_WKUP_CONTROL_CLKCTRL) & (0x03<<16) != 0x00 );
	while(*((unsigned int *)CM_L3_AON_CLKSTCTRL) & (0x01<<3) != 0x00 );		
	while(*((unsigned int *)CM_WKUP_ADC_TSC_CLKCTRL) & (0x03<<16) != 0x00 );

	SET_STEPCONFIG_WRITE_PROTECT;
	SET_CONFIG;
	// #include<AnalogInitialize.h>		
	SET_ADC;
	return OK;
}
