#include <unity.h>

#ifdef ARDUINO  
#include <Arduino.h>   // needed for service delay
#endif

#include "log.h"





void setUp(void) 
{
  // set stuff up here
}

void tearDown(void) 
{
  // clean stuff up here
}



void test_case_1(void) 
{
}



void setup()
{
#ifdef ARDUINO  
    delay(2000); // service delay
#endif    
    UNITY_BEGIN();

    RUN_TEST(test_case_1);

    UNITY_END(); // stop unit testing
}



void loop()
{
}


#ifndef ARDUINO
// only needed if unit test is running in an native environment
int main(int argc, char *argv[])
{
  setup();
  loop();
  return 0;
}
#endif