#ifdef ARDUINO 
#include <Arduino.h> 
#else
#include <iostream>
#endif

#include "debug.h"

class DebugAction : public DebugActionInterface
{
public: 
  void Callback(const char* pc_Message);
};

void DebugAction::Callback(const char* pc_Message)
{
#ifdef ARDUINO  
  Serial.println(pc_Message);
#else
  printf("%s\n", pc_Message);
//  std::cout << pc_Message << std::endl;
#endif
}


DebugAction g_debugAction;
Debug g_debug;



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

  g_debug.init(&g_debugAction, Debug::Info);
}



void loop()
{
  g_debug.msg(Debug::Info, "loop successfully entered - exiting...");
#ifdef ARDUINO  
  Serial.flush();
#endif

  // This is only for demonstration, we don't want this 
  // program to run forever, so we exit the program at this point. 
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
