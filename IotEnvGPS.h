#ifndef IOTENVGPS_h
#define IOTENVGPS_h

#include "IoTEnvConfig.h"
#include "WString.h"

class IOTENVGPS{
public:
  void on();
  void getGPSLocation(double *lat, double *lon); /*Retorna Latitude e Longitude*/
};

#endif
