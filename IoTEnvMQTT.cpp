#include "IoTEnvMQTT.h"
#include "GSM_MQTT.h"

String MQTT_HOST = _broker_url;
String MQTT_PORT = _broker_porta;
char * dispositivo = "tcc-bruno";

GSM_MQTT MQTT(20);

void IOTENVMQTT::on(){
	MQTT.gsmOn();
}

void IOTENVMQTT::enviarMensagem(String mensagem){
	MQTT.begin();
	while(!MQTT.available()){
		MQTT.processing();
	}
	
	Serial.println("MQTT DISPONIVEL");
	char m[mensagem.length()];
  mensagem.toCharArray(m, mensagem.length());

  MQTT.publish(0, 0, 0, 120, _broker_topico, m);
}
