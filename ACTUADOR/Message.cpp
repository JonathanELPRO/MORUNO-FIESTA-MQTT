#include "Message.h"


Message::Message() {
  
}

Message::~Message() {
  
}


String Message::getValue() {
  return value;
}


void Message::setValue(String value) {
  this->value = value;
}


float Message::getValueInFloat(){
  return value.toFloat(); 
}
