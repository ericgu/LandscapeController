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

#ifdef ESP8266
    extern "C" {
        #include "user_interface.h"
    }
#endif

ADC_MODE(ADC_TOUT);

Manager manager;
WebServer webServer(&manager);
HardWiredController hardWiredController(&manager);

static const int STAIR_SENSE_PIN = 16;
bool stairLightsOn = false;
 

void setup()
{
  Serial.begin(115200);
 
  pinMode(STAIR_SENSE_PIN, INPUT);

  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect("LandscapeController");

  webServer.Init();
}

void SetHouseLights(char* actionString)
{
    Serial.print("House lights: "); Serial.println(actionString);

    String a = String(actionString);
    Action action(a);
    String resource("house");
    manager.DoCommand(action, resource); 
}

void HandleStairSense()
{
  // Sense 12V input and send appropriate command if it has changed.
  
  bool stairSense = digitalRead(STAIR_SENSE_PIN);

  if (stairSense && !stairLightsOn)
  {
    SetHouseLights("on");
    stairLightsOn = true;
  }
  else if (!stairSense && stairLightsOn)
  {
    SetHouseLights("off");
    stairLightsOn = false;
  }
}

void loop() 
{
  webServer.Handle();

  HandleStairSense();

  hardWiredController.Handle();

  // handle timeouts to switch off if accidently left on.
  // flash outputs 5 minutes before turning off...

  delay(10);  // run at 100Hz or so...
}
