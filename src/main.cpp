#ifdef ARDUINO 
#include <Arduino.h> 
#else
#include <iostream>
#endif


#include "debug.h"


void debug_callback(const char* pc_Message)
{
#ifdef ARDUINO  
  Serial.println(pc_Message);
#else
  std::cout << pc_Message << std::endl;
#endif
}



void setup()
{ 
#ifdef ARDUINO
  Serial.begin(115200);
  Serial.println(__LIBRARY_NAME__);
  Serial.println(__DATE__ " " __TIME__);
#else
  std::cout << __LIBRARY_NAME__ << std::endl;
  std::cout << __DATE__ " " __TIME__ << std::endl;
#endif

  debug_init(&debug_callback, Info);
}



void loop()
{
  static volatile uint8_t value = 0;
  value++;   // do something very simple

  debug(Info, "loop successfully entered - exiting...");
#ifdef ARDUINO  
  Serial.flush();
#endif
  exit(0);
}



#ifndef ARDUINO  
int main(int argc, char *argv[])
{
  setup();
  while(true)
    loop();
  return 0;
}
#endif
