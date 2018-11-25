#define TINY_GSM_MODEM_SIM808

#include "IoTEnvMQTT.h"
#include <TinyGsmClient.h>
#include "PubSubClient.h"

/*MQTT*/
#define SerialMon Serial
#define SerialAT Serial1

const char* broker = "broker.hivemq.com";
char disp[] = "tcc-bruno";
char topi[] = "iotenv";
const char* topicInit = "GsmClientTest/brunofreitas";
const char apn[]  = "gprs.oi.com.br";
const char user[] = "oi";
const char pass[] = "oi";

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

int mensagemEnviada = 0;
long lastReconnectAttempt = 0;


void IOTENVMQTT::on(){
// Set console baud rate
	SerialMon.begin(9600);
	delay(10);

  	// Set GSM module baud rate
  	SerialAT.begin(2400);
  	delay(3000);
	SerialMon.println("Initializing modem...");
	modem.restart();
	mqtt.setServer(broker, 1883);
}

boolean mqttConnect(String mensagem){
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  boolean status = mqtt.connect("tcc-bruno");

  // Or, if you want to authenticate MQTT:
  //boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");

  if (status == false) {
    SerialMon.println(" fail");
    return false;
  }
  
  SerialMon.println("Conectado ao broker");
  char m[mensagem.length()];
  mensagem.toCharArray(m, mensagem.length()+1);
  mensagemEnviada = mqtt.publish(topicInit, m);
 
  SerialMon.println(strlen(m));

  return mensagemEnviada;
}

void IOTENVMQTT::enviarMensagem(String mensagem){
	mensagemEnviada = 0;
	modem.restart();
	String modemInfo = modem.getModemInfo();
	SerialMon.print("Modem: ");
	SerialMon.println(modemInfo);

	SerialMon.print("Waiting for network...");
	if (!modem.waitForNetwork()) {
		SerialMon.println(" fail");
		while (true);
	}
	SerialMon.println(" OK");

	SerialMon.print("Connecting to ");
	SerialMon.print(apn);
	if (!modem.gprsConnect(apn, user, pass)) {
		SerialMon.println(" fail");
		while (true);
	}

	if (!mensagemEnviada) {
		if(!mqtt.connected()){
			SerialMon.println("=== MQTT NOT CONNECTED ===");
    		// Reconnect every 10 seconds
    		unsigned long t = millis();
    		if (t - lastReconnectAttempt > 10000L) {
      			lastReconnectAttempt = t;
      			if (mqttConnect(mensagem)) {
					SerialMon.println("Mensagem enviada");
        			lastReconnectAttempt = 0;
					mensagemEnviada = true;
      			}
   			}
		}

		mqtt.loop();
    	delay(100);
  	}

}
