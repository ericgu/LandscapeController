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

public:
    WebServer(Manager* pManager)
    {
        _pManager = pManager;
        _pServer = new ESP8266WebServer(80);
        _pWebServer = this;
    }

    void Init()
    {
         Serial.print("IP address: ");
         Serial.println(WiFi.localIP());  //Print the local IP
 
        _pServer->on("/", handleMainPage);    //Associate the handler function to the path
        _pServer->on("/command", handleCommand);
        _pServer->begin();                    //Start the server
        Serial.println("Server listening");
    }

    void Handle()
    {  
        _pServer->handleClient();         //Handling of incoming requests
    }

};

WebServer* WebServer::_pWebServer = 0;