if(strcmp(devptr->dvname,"TMP_SENSOR")==0)
(*((unsigned int *)STEP_CONFIG1) |= (1<<19));