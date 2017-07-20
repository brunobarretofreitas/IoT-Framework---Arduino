#include "IoTEnvMQTT.h"
#include "GSM_MQTT.h"

/*MQTT*/

char disp[] = "tcc-bruno";
char topi[] = "iotenv";

void GSM_MQTT::AutoConnect(void){connect(disp, 0, 0, "", "", 1, 0, 0, 0, "", "");}
void GSM_MQTT::OnConnect(void){Serial.println("Conectado ao Broker");}
void GSM_MQTT::OnMessage(char *Topic, int TopicLength, char *Message, int MessageLength){}

String MQTT_HOST = _broker_url;
String MQTT_PORT = _broker_porta;
String MQTT_TOPICO = _broker_topico;

GSM_MQTT MQTT(20);


void IOTENVMQTT::on(){
	MQTT.gsmOn();
}

void IOTENVMQTT::enviarMensagem(String mensagem){
	bool mensagem_enviada = false;
	MQTT.begin();
	delay(5000);
	while(!mensagem_enviada){
		if(MQTT.available()){
			Serial.println("MQTT Disponível");		
			char m[mensagem.length()];
			mensagem.toCharArray(m, mensagem.length()+1);
			MQTT.publish(0, 0, 0, "iotmessage", topi, m);
		}

		mensagem_enviada = MQTT.publishSent();
		Serial.print("O MQTTSENT DEU ");
		Serial.println(mensagem_enviada);
		MQTT.processing();
		delay(5000);
	}
}
