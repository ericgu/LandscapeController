#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
//#include "WifiManager.h"

#include "UdpLogger.h"
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

//UdpLogger udpLogger("LandscapeController: ", 12345);
Manager manager;
WebServer webServer(&manager/*, &udpLogger*/);
HardWiredController hardWiredController(&manager);
StairSensing stairSensing(&manager);

void setup()
{
  Serial.begin(115200);
 
  char ssid[] = "DozerNet";
  char password[] = "Gunnerson";

  IPAddress ip(192, 168, 1, 200);
  IPAddress gateway(192, 168, 1, 5);
  IPAddress subnet(255, 255, 255, 0);

  //WiFiManager wifiManager;
  //wifiManager.resetSettings();
  //wifiManager.autoConnect("LandscapeController");
  
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  webServer.Init();
  UdpLogger.Init(12345, "LandscapeController: ");
  UdpLogger.WriteStartMessage();
}

int heartbeat = 0;
void loop() 
{
  heartbeat++;
  if (heartbeat > 100 * 60) // one message per minute
  {
    //sendUdp();
    heartbeat = 0;
    UdpLogger.print("LandscapeController ");
    UdpLogger.println(WiFi.localIP());
    Serial.println("Heartbeat...");
  }

  webServer.Handle();

  stairSensing.Handle();

  hardWiredController.Handle();

  manager.HandleTimeout();

  delay(10);  // run at 100Hz (ish)
}
