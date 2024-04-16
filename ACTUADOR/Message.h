#include <Arduino.h>

class Message {
  private:
    String value;

  public:
    
    Message();

    ~Message();
    
    String getValue();

    
    void setValue(String value);

    float getValueInFloat();
    
};
