#include "MqttManager.h"



MqttManager::MqttManager() {
    WiFiClient* wiFiClient =new WiFiClient();
    mqttClient = new PubSubClient(*wiFiClient);
}

MqttManager::~MqttManager() {
    delete mqttClient;
}



bool MqttManager::theConnectionIsStillStanding() {
    return mqttClient->connected();
}

String MqttManager::castCharacterVectorToString(char * characterVector){
  return String(characterVector);
}


void MqttManager::checkIfTheConnectionIsStillStandingAndDoTheCallBack() {
    if (theConnectionIsStillStanding()) {
         mqttClient->loop();      
    }
    else {
        Serial.println("MQTT broker not connected!");  
        delay(2000);
    }
}

void MqttManager::setServer_(char * host, int port) {
    mqttClient->setServer(host, port); 
}

void MqttManager::setCallback_(void (*callBack)(const char *, byte *, unsigned int)) {
    mqttClient->setCallback(*callBack);  
}

bool MqttManager::stablishConnectionWithTheServer(char* mqttClientId) {
    return mqttClient->connect(mqttClientId);
}

void MqttManager::subscribeToTopic(char* topic) {
    mqttClient->subscribe(topic);
}

void MqttManager::establishConnectionWithTheServerAndSubscribeToTopic(char* host, char* mqttClientId, char* topic) {
    Serial.print("Connecting to " + castCharacterVectorToString(host));
    if (stablishConnectionWithTheServer(mqttClientId)) {
        Serial.println(" Connected!");
        subscribeToTopic(topic);
    }
}
