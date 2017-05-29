#ifndef IOTENVGPS_h
#define IOTENVGPS_h

#include "IoTEnvConfig.h"
#include "WString.h"

class IOTENVGPS{
public:
  IOTENVGPS();
  void getGPSLocation(String *lat, String *lon); /*Retorna Latitude e Longitude*/
};

#endif
