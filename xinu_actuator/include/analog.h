#define CM_WKUP					0x44E00400

#define CM_WKUP_CLKSTCTRL                     	0x44E00400
#define CM_WKUP_CONTROL_CLKCTRL               	0x44E00404
#define CM_WKUP_L4WKUP_CLKCTRL                	0x44E0040C
#define CM_L3_AON_CLKSTCTRL                   	0x44E00418
#define CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL	0x44E004CC
		
#define CM_WKUP_ADC_TSC_CLKCTRL			0x44E004BC

#define ADC_TSC_ADDR				0x44E0D000
#define CONTROL_REG				0x44E0D040
#define STEP_ENABLE				0x44E0D054
#define STEP_CONFIG1				0x44E0D064
#define FIFO0					0x44E0D100
#define FIFO0Count				0x44E0D0E4

#define SET_STEPCONFIG_WRITE_PROTECT		(*((unsigned int *)CONTROL_REG) &= (1<<2))

#define SET_ADC		(*((unsigned int *)CONTROL_REG) |= (1))

#define SET_CM_WKUP_CONTROL_CLKCTRL	(*((unsigned int *)CM_WKUP_CONTROL_CLKCTRL) |= (1<<1))
#define SET_CM_WKUP_CLKSTCTRL		(*((unsigned int *)CM_WKUP_CLKSTCTRL) |= (1<<1))
#define SET_CM_L3_AON_CLKSTCTRL		(*((unsigned int *)CM_L3_AON_CLKSTCTRL) |= (1<<1))

#define SET_CM_WKUP_ADC_TSC_CLKCTRL (*((unsigned int *)CM_WKUP_ADC_TSC_CLKCTRL) |= (1<<1))
#define SET_ENABLE	(*((unsigned int *)STEP_ENABLE) |= (1<<1))
#define SET_DISABLE	(*((unsigned int *)STEP_ENABLE) &= ~(1<<1))
#define SET_CONFIG	(*((unsigned int *)STEP_CONFIG1) |= (1<<1))
#define READ_FIFO	(*((unsigned int *)FIFO0) &= (0xfff))
#define READ_FIFO_Count	(*((unsigned int *)FIFO0Count))
#define CELSIUS_FORMULA(n)	(n-500)/10
#define FAHR_FORMULA(n)		(n*9/5)+32

#define HWREG(n)	(*((volatile unsigned int *)(n)))
