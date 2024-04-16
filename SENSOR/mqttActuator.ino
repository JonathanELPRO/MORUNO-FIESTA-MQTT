#include "MqttManager.h"
#include "UltrasonicSensor.h"

const char * WIFI_SSID = "UCB-PREMIUM";
const char * WIFI_PASS = "lacatoucb";

const int TRIGGER=18;
const int ECHO=19;

char * MQTT_BROKER_HOST = "broker.hivemq.com";
int MQTT_BROKER_PORT = 1883;
char * MQTT_CLIENT_ID = "kldfsfdsjln";       
char * PUBLISH_TOPIC = "pruebita/6";    
char * SUBSCRIBE_TOPIC = "pruebita/6";

MqttManager* mqttManager=new MqttManager();
UltrasonicSensor* ultrasonicSensor=new UltrasonicSensor(TRIGGER,ECHO);

void setup() {
  Serial.begin(115200);
  WifiManager *wifiManager = new WifiManager(WIFI_SSID, WIFI_PASS);
  wifiManager->connectToWifi();
  mqttManager->setServer_(MQTT_BROKER_HOST,MQTT_BROKER_PORT);
  mqttManager->establishConnectionWithTheServerAndSubscribeToTopic(MQTT_BROKER_HOST ,MQTT_CLIENT_ID, SUBSCRIBE_TOPIC); 
}

unsigned long previousPublishMillis = 0;

void loop() {
    float distance=ultrasonicSensor->returnDistancInCentimeters();
    Serial.print(distance);
    mqttManager->checkIfTheConnectionIsStillStandingAnnPublish(previousPublishMillis, distance, PUBLISH_TOPIC);  
}
