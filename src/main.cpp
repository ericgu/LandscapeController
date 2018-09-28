#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WifiManager.h"

#include "manager.h"
#include "action.h"
#include "device.h"
#include "WebServer.h"
//#include "wifi.h"
#include "HardWiredController.h"
#include "StairSensing.h"

#ifdef ESP8266
    extern "C" {
        #include "user_interface.h"
    }
#endif

ADC_MODE(ADC_TOUT);

Manager manager;
WebServer webServer(&manager);
HardWiredController hardWiredController(&manager);
StairSensing stairSensing(&manager);

void setup()
{
  Serial.begin(115200);
 
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("LandscapeController");

  webServer.Init();
}

void loop() 
{
  webServer.Handle();

  stairSensing.Handle();

  hardWiredController.Handle();

  manager.HandleTimeout();

  delay(10);  // run at 100Hz (ish)
}
