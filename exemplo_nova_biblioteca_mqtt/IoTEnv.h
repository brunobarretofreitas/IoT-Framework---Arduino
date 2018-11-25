#include "WString.h"
#ifndef IOTENV_H
#define IOTENV_H
#endif

#include <ArduinoJson.h>
#include <Arduino.h>
#include "IoTEnvData.h"

class IOTENV{
private:
	void clearArray(JsonArray& a);

public:
	IOTENV(unsigned long interColeta); 
	unsigned long intervaloColeta;
	void start();
	void processar();

  	void enviarDados();
	void getLocalizacao();
	void coletarDados(); /*Função onde os dados serão setados*/
	void addDadoColetado(String nome, String valor); /*Função chamada dentro de coletarIndices para adicionar um indice coletado*/

	void intColeta();
};
