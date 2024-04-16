#include "Led.h"

class LedsController {
private:
    Led* redLed;
    Led* yellowLed;
    Led* greenLed;
public:
    LedsController(Led* redLed, Led* yellowLed, Led* greenLed);
    ~LedsController();
    void turnLedsOnOrOffBasedOnDistance(float distance);
    
};
