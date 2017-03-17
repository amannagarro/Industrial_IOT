if(strcmp(devptr->dvname,"TMP_SENSOR")==0)
temp_degrees = (uint32)(((milliVolts/1023)*3.3)-0.5)*(1000/10);
