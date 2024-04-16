#include "LedsController.h"

LedsController::LedsController(Led* redLed, Led* yellowLed, Led* greenLed) {
    this->redLed = redLed;
    this->yellowLed = yellowLed;
    this->greenLed = greenLed;
}

LedsController::~LedsController() {
    delete redLed;
    delete yellowLed;
    delete greenLed;
}

void LedsController::turnLedsOnOrOffBasedOnDistance(float distance){
    redLed->turnOff(); 
    yellowLed->turnOff(); 
    greenLed->turnOff(); 
                if (distance >= 2.0 && distance < 6.0) {
                redLed->turnOn(); 
                
              } else if (distance >= 6.0 && distance < 10.0) {
                
                yellowLed->turnOn(); 
                
              } else if (distance >= 10.0) {
                
                greenLed->turnOn(); 
              }
}
