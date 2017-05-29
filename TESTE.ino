#include "IoTEnv.h"
#include <SimpleDHT.h>
#define  pinDHT11 A1


char* dispositivo = "tcc-bruno"; /*Identificador do Dispositivo*/
char* brokerHost = "broker.mqttdashboard.com"; /*MQTT - Host do Broker*/
char* brokerPorta = "1883"; /*MQTT - Porta do Broker*/
char* topico = "iotenv"; /*MQTT - Topico*/
long intervaloColeta = 5000; /*Tempo em milisegundos*/

IOTENV iot(dispositivo, brokerHost, brokerPorta, topico, intervaloColeta);

int MQ135 = A0;
SimpleDHT11 dht11;
int som = A5;


void IOTENV::coletarIndices(){
  /**
  TODOS OS DADOS DEVERÃO SER COLETADOS E ADICIONADOS AO FRAMEWORK NESTA FUNÇÃO
  Ex: 
  temperatura = DHT.temperatura();
  IOT.addIndice("temperatura", String(temperatura));
  umidade = DHT.umidade();
  IOT.addIndice("umidade", String(umidade)); 
  */
//  int co2 = analogRead(MQ135);
//  byte temperature = 0;
//  byte humidity = 0;
//  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
//    Serial.println("Read DHT11 failed.");
//    return;
//  }
//  
//  int ruido = analogRead(sound_analogico);

  Serial.println("Coletar Indices foi chamada");
  iot.addIndice("CO2", String(30));
  iot.addIndice("temperatura", String(20));
  iot.addIndice("umidade", String(20));
  iot.addIndice("som", String(20));
}



void setup(){
  iot.start();
}

void loop(){
  iot.process(); /*É nesta função em que os dados serão coletados e enviados no intervalo determinado*/
}
