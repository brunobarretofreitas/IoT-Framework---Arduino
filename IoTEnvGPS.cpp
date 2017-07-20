#include "IoTEnvGPS.h"
/*IMPORTS NECESSÁRIOS PARA FUNCIONAMENTO DO HOT SPOT*/
#include "gps.h"
#include <stdlib.h>
/**/

GPSGSM gps_gsm;

void IOTENVGPS::on(){}

void IOTENVGPS::getGPSLocation(double *lat, double *lon){
	if (gps_gsm.attachGPS()){
		Serial.println("status=GPSREADY");
		delay(20000); //Time for fixing
	}else{
		Serial.println("status=ERROR");
	}

	Serial.println("Getting GPS data");
  	int stat = 0;
	while(stat!=2 && stat!=3){
		stat=gps_gsm.getStat();
	    switch(stat){
	      case 1: Serial.println("NOT FIXED");
	      break;
	      case 2: Serial.println("2D FIXED");
	      break;
	      case 3: Serial.println("3D FIXED");
	      break;
	    }
	  }

	char lo[15];
	char la[15];
	char alt[15];
	char time[20];
	char vel[15];

	gps_gsm.getPar(la,lo,alt,time,vel);

	Serial.println(lo);
	Serial.println(la);
	Serial.println(alt);
	Serial.println(time);
	Serial.println(vel);

	*lat = atof(la);
	*lon = atof(lo);

	gps_gsm.deattachGPS();
}
