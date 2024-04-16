#include <PubSubClient.h>
#include "WifiManager.h"


class MqttManager {
private:
    PubSubClient* mqttClient;
    
public:
    MqttManager();
    ~MqttManager();
    
    bool theConnectionIsStillStanding();
    String castCharacterVectorToString(char * characterVector);
    void checkIfTheConnectionIsStillStandingAnnPublish(unsigned long& previousPublishMillis,float distance, char* publishTopic);
    void setServer_(char * host, int port);
    void setCallback_(void (*callBack)(const char *, byte *, unsigned int));
    bool stablishConnectionWithTheServer(char* mqttClientId);
    void subscribeToTopic(char* topic);
    void establishConnectionWithTheServerAndSubscribeToTopic(char* host, char* mqttClientId, char* topic);
    
};
