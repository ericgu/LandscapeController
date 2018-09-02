#include "MainPage.h"
#include "persistentstorage.h"

class Networks
{
  public:

  int count;
  String* pValues;
};

class WiFiManager
{
    public:
    static WiFiManager* _pWiFiManager;

    ESP8266WebServer* _pServer;
    Manager* _pManager;
    Networks _networks;

private:

    void LoadNetworks()
    {
      int n = WiFi.scanNetworks();
      Serial.print("Found networks: ");
      Serial.println(n);

      _networks.count = n * 2;
      _networks.pValues = new String[_networks.count];
      
      for (int i = 0; i < n; ++i) {
        String ssid = WiFi.SSID(i);
        if (!ssid.startsWith("EDP_"))
        {   
          _networks.pValues[i * 2] = ssid;

          long rssi = WiFi.RSSI(i);
          int percentage = 2 * (rssi + 100);
          if (percentage > 100)
          {
            percentage = 100;
          }
          else if (percentage < 0)
          {
            percentage = 0;
          }

          char number[10];
          itoa(percentage, number, 10);

          String display = ssid;
          display += " (";
          display += percentage;
          display += "%)";

          _networks.pValues[i * 2 + 1] = display;
        }
      }
    }

    static void handleMainPage() {            //Handler for the rooth path
 
        String result = MainPageHtml1;

        result += _pWiFiManager->_pManager->GetStatus();

        result += MainPageHtml2;

         _pWiFiManager->_pServer->send(200, "text/html", result);
    }

    static void handleCommand() 
    {
       String resource;

        if (_pWiFiManager->_pServer->hasArg("r"))
        {
            resource = _pWiFiManager->_pServer->arg("r");
        }

        Action action;

        if (_pWiFiManager->_pServer->hasArg("a"))
        {
            action = Action(_pWiFiManager->_pServer->arg("a"));
        }

        _pWiFiManager->_pManager->DoCommand(action, resource);

       _pWiFiManager->_pServer->sendHeader("Location", String("/"), true);
       _pWiFiManager->_pServer->send ( 302, "text/plain", "");
       // redirect...
    }

    static void OnProvision()
    {
      if (_pWiFiManager->_pServer->hasArg("ssid"))
      {
        String ssid = _pWiFiManager->_pServer->arg("ssid");
        String password = _pWiFiManager->_pServer->arg("password");

        Serial.print("  ssid: "); Serial.println(ssid);
        Serial.print("  password: "); Serial.println(password);
        _pWebServer->_pWifiHandler->setWirelessParametersAndRestart(ssid, password, true);

        _pWiFiManager->_pServer->send(200, "text/html", "<h1>Provisioning...</h1><html>Disconnect from this wireless network and reconnect to your main network.</html>");
      }      
      else
      {
        String response = ProvisionPageHtml1;

        response += ProvisionPageHtml2;

        for (int i = 0; i < _pWiFiManager->_networks.count; i += 2)
        {
          String option = "<option value=\"" + _pWiFiManager->_networks.pValues[i] + "\">" + _pWiFiManager->_networks.pValues[i + 1] + "</option>";
          response += option;
        }

        response += ProvisionPageHtml3;
        _pWiFiManager->_pServer->send(200, "text/html", response);
      }

      Serial.println("< Provision");
    }

public:
    WiFiManager(Manager* pManager)
    {
        _pManager = pManager;
        _pServer = new ESP8266WebServer(80);
        _pWiFiManager = this;
    }

    void Init()
    {
        LoadNetworks();

        WiFi.begin("DozerNet", "Gunnerson");  //Connect to the WiFi network
 
        while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
           delay(500);
          Serial.println("Waiting to connect…");
 
         }
 
         Serial.print("IP address: ");
         Serial.println(WiFi.localIP());  //Print the local IP
 
        _pServer->on("/", handleMainPage);    //Associate the handler function to the path
        _pServer->on("/command", handleCommand);
        _pServer->on("/provision", OnProvision);
        _pServer->begin();                    //Start the server
        Serial.println("Server listening");
    }

    void Handle()
    {  
        _pServer->handleClient();         //Handling of incoming requests
    }

};

WiFiManager* WiFiManager::_pWiFiManager = 0;