#ifndef IOTENVMQTT_h
#define IOTENVMQTT_h

#include "WString.h"
#include "IoTEnvConfig.h"

class IOTENVMQTT{
public:
  void on();
  void enviarMensagem(String mensagem);
};

#endif
