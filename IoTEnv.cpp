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
JsonArray& local = root.createNestedArray("local");

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
  for(int i = 0; i < a.size() + 1; i++) a.remove(0);
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
  Serial.println(mensagem);
  clearArray(dados);
  clearArray(local);

  iotMqtt.enviarMensagem(mensagem);
}

void IOTENV::getLocalizacao(){
  double lat = 0.0;
  double lon = 0.0;

  iotGps.getGPSLocation(&lat, &lon);

  Serial.print("latitude: ");
  Serial.print(lat);
  Serial.print("longitude: ");
  Serial.print(lon);
  local.add(lat);
  local.add(lon);
}

void IOTENV::addIndice(String nome, String valor){
  JsonObject& _dado = dados.createNestedObject();
  _dado["nome"] = nome;
  _dado["valor"] = valor;
}
