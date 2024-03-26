#include <unity.h>

#ifdef ARDUINO  
#include <Arduino.h>   // needed for service delay
#endif

#include <string.h>
#include "debug.h"


uint32_t gu32_CallbackCounter;
char gac_CallbackMessage[256]="";



class DebugAction : public DebugActionInterface
{
public: 
  void Callback(const char* pc_Message);
};

void DebugAction::Callback(const char* pc_Message)
{
  gu32_CallbackCounter++;
  strcpy(gac_CallbackMessage, pc_Message);
}


DebugAction g_debugAction;
Debug g_debug;







void setUp(void) 
{
  // set stuff up here
  gu32_CallbackCounter = 0;
}

void tearDown(void) 
{
  // clean stuff up here
}




void testcase_log_unconfigured(void) 
{
  g_debug.msg(Debug::Error, "This is an error");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, gu32_CallbackCounter, "callback called even though not configured");
}

void testcase_log_configured(void) 
{
  g_debug.init(&g_debugAction);

  g_debug.msg(Debug::Error, "This is an error");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, gu32_CallbackCounter, "callback not called for error");
  TEST_ASSERT_EQUAL_STRING("ERROR: This is an error", gac_CallbackMessage);

  g_debug.msg(Debug::Warning, "This is a warning");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, gu32_CallbackCounter, "callback called even though warnings shouldn't be logged be default");
  g_debug.msg(Debug::FatalError, "This is a fatal error");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, gu32_CallbackCounter, "callback not called for fatal error");

  g_debug.finish();
  g_debug.msg(Debug::Error, "This is an error");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, gu32_CallbackCounter, "callback called after finish");
}


void setup()
{
#ifdef ARDUINO  
    delay(2000); // service delay
#endif    
    UNITY_BEGIN();

    RUN_TEST(testcase_log_unconfigured);
    RUN_TEST(testcase_log_configured); 

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