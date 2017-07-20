#include "WString.h"
#include "IoTEnv.h"
#include "GSM_MQTT.h"
#include "gps.h"
#include "IoTEnvConfig.h"
#include "IoTEnvMQTT.h"
#include "IoTEnvGPS.h"

IOTENVMQTT iotMqtt;
IOTENVGPS iotGps;

DynamicJsonBuffer jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
JsonArray& dados = root.createNestedArray("dados");
JsonObject& localizacao = root.createNestedObject("localizacao");

IOTENV::IOTENV(unsigned long interColeta){
  intervaloColeta = interColeta;
}

void IOTENV::start(){
  Serial.println("IoTEnv Start");
  root["dispositivo"] = _dispositivo;
  iotMqtt.on();
  iotGps.on();
}

void IOTENV::clearArray(JsonArray& a){
  for(int i = 0; i < a.size(); i++) a.remove(0);
  a.remove(0);
}

void IOTENV::intColeta(){
  delay(intervaloColeta * 1000);
}

void IOTENV::processar(){
  getLocalizacao();
  coletarDados();
  enviarDados();
  intColeta();
}

void IOTENV::enviarDados(){
  String mensagem;
  root.printTo(mensagem);
  char m[mensagem.length()];
  mensagem.toCharArray(m, mensagem.length()+1);
  Serial.println(m);
  clearArray(dados);
  localizacao.remove("longitude");
  localizacao.remove("latitude");
  
  iotMqtt.enviarMensagem(mensagem);
}

void IOTENV::getLocalizacao(){
  double lat = 0.0;
  double lon = 0.0;

  iotGps.getGPSLocation(&lat, &lon);
  localizacao["longitude"] = lon;
  localizacao["latitude"] = lat;
}

void IOTENV::addDadoColetado(String nome, String valor){
  JsonObject& _dado = dados.createNestedObject();
  _dado["nome"] = nome;
  _dado["valor"] = valor;
}