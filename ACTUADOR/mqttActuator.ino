#include "MqttManager.h"
#include "LedsController.h"
#include "Message.h"

Led* redLed = new Led(18, "R");
Led* yellowLed = new Led(19, "Y");
Led* greenLed = new Led(21, "G");

const char * WIFI_SSID = "UCB-PREMIUM";
const char * WIFI_PASS = "lacatoucb";

char * MQTT_BROKER_HOST = "broker.hivemq.com";
int MQTT_BROKER_PORT = 1883;

char * MQTT_CLIENT_ID = "jhsabdsahlb";       
char * PUBLISH_TOPIC = "pruebita/6";    
char * SUBSCRIBE_TOPIC = "pruebita/6";

MqttManager* mqttManager=new MqttManager();
LedsController* ledsController=new LedsController(redLed, yellowLed, greenLed);
Message* message=new Message();

char castPointerByteToCharacter(byte * byte_) {
    return (char) *byte_;
}

String castCharacterToString(char character) {
    return String(character);
}

String getMessageFromPayload(byte * payload, unsigned int length) {
    String messageString;
    for (int i = 0; i < length; i++) messageString += castCharacterToString(castPointerByteToCharacter(&payload[i]));
    return messageString;
}

String castCharacterVectorToString(const char * characterVector) {
    return String(characterVector);
}

bool theCallbackTopicIsTheSubscribedTopic(const char * topic) {
    return castCharacterVectorToString(topic) == SUBSCRIBE_TOPIC;
}

void turnLedsOnOrOffBasedOnDistance(float distance) {
    ledsController->turnLedsOnOrOffBasedOnDistance(distance);
}

void checkTheSuscribeTopicAndShowTheMessage(const char * topic, Message* message) {
    if (theCallbackTopicIsTheSubscribedTopic(topic)) {
        Serial.println("Message from topic " + castCharacterVectorToString(topic) + ":" + message->getValue());
    }
}

void callBack(const char * topic, byte * payload, unsigned int length) {
    message->setValue(getMessageFromPayload(payload, length));
    checkTheSuscribeTopicAndShowTheMessage(topic, message);
}

void setup() {  
  Serial.begin(115200);
  WifiManager *wifiManager = new WifiManager(WIFI_SSID, WIFI_PASS);
  wifiManager->connectToWifi(); 
  mqttManager->setServer_(MQTT_BROKER_HOST,MQTT_BROKER_PORT);
  mqttManager->setCallback_(&callBack);
  mqttManager->establishConnectionWithTheServerAndSubscribeToTopic(MQTT_BROKER_HOST ,MQTT_CLIENT_ID, SUBSCRIBE_TOPIC); 
}

void loop() {
    mqttManager->checkIfTheConnectionIsStillStandingAndDoTheCallBack();
    float distance=message->getValueInFloat();
    ledsController->turnLedsOnOrOffBasedOnDistance(distance);
}
