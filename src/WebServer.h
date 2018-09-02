#include "MainPage.h"

class WebServer
{
    public:
    static WebServer* _pWebServer;

    ESP8266WebServer* _pServer;
    Manager* _pManager;

private:

    static void handleMainPage() { 
 
        String result = MainPageHtml1;

        result += _pWebServer->_pManager->GetStatus();

        result += MainPageHtml2;

         _pWebServer->_pServer->send(200, "text/html", result);
    }

    static void handleCommand() 
    {
       String resource;

        if (_pWebServer->_pServer->hasArg("r"))
        {
            resource = _pWebServer->_pServer->arg("r");
        }

        Action action;

        if (_pWebServer->_pServer->hasArg("a"))
        {
            action = Action(_pWebServer->_pServer->arg("a"));
        }

        _pWebServer->_pManager->DoCommand(action, resource);

        _pWebServer->_pServer->sendHeader("Location", String("/"), true);
        _pWebServer->_pServer->send ( 302, "text/plain", "");
        // redirect...
    }

#if fred
    static void OnProvision()
    {
      if (_pWebServer->_pServer->hasArg("ssid"))
      {
        String ssid = _pWebServer->_pServer->arg("ssid");
        String password = _pWebServer->_pServer->arg("password");

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
        _pWebServer->_pServer->send(200, "text/html", response);
      }

      Serial.println("< Provision");
    }
#endif

public:
    WebServer(Manager* pManager)
    {
        _pManager = pManager;
        _pServer = new ESP8266WebServer(80);
        _pWebServer = this;
    }

    void Init()
    {
#if fred
        WiFi.begin("DozerNet", "Gunnerson");  //Connect to the WiFi network
 
        while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
           delay(500);
           Serial.println("Waiting to connect…");
         }
 #endif
 
         Serial.print("IP address: ");
         Serial.println(WiFi.localIP());  //Print the local IP
 
        _pServer->on("/", handleMainPage);    //Associate the handler function to the path
        _pServer->on("/command", handleCommand);
        //_pServer->on("/provision", OnProvision);
        _pServer->begin();                    //Start the server
        Serial.println("Server listening");
    }

    void Handle()
    {  
        _pServer->handleClient();         //Handling of incoming requests
    }

};

WebServer* WebServer::_pWebServer = 0;