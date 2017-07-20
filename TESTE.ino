#include "IoTEnv.h"
#include <SimpleDHT.h>
#define  pinDHT11 A1

IOTENV iot(20);
int MQ135 = A0;
SimpleDHT11 dht11;

void IOTENV::coletarDados(){
    int co2 = analogRead(MQ135);
    byte temperature = 0;
    byte humidity = 0;
    if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
      Serial.println("Read DHT11 failed.");
      return;
    }
    
  iot.addIndice(_CO2, String(co2));
  iot.addIndice(_TEMPERATURA, String(temperature));
  iot.addIndice(_UMIDADE, String(humidity));
}

void setup(){
  Serial.begin(9600);
  iot.start();
}

void loop(){
  iot.processar();
}
