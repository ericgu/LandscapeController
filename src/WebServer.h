#include "MainPage.h"

class WebServer
{
    public:
    static WebServer* _pWebServer;

    ESP8266WebServer* _pServer;
    Manager* _pManager;
    //UdpLogger* _pUdpLogger;

private:

    static void handleMainPage() { 
 
        String result = MainPageHtml1;

        result += _pWebServer->_pManager->GetStatus();

        result += MainPageHtml2;

         _pWebServer->_pServer->send(200, "text/html", result);
    }

    static void handleCommandStatic()
    {
        _pWebServer->handleCommand();
    }

    void handleCommand() 
    {
        String resource;

        if (_pServer->hasArg("r"))
        {
            resource = _pWebServer->_pServer->arg("r");
        }

//        _pUdpLogger->print("Resource, Action: ");
//        _pUdpLogger->print(resource);
        UdpLogger.print("Resource, Action: ");
        UdpLogger.print(resource);
        
        Action action;

        if (_pServer->hasArg("a"))
        {
            action = Action(_pServer->arg("a"));
//            _pUdpLogger->print(", ");
//            _pUdpLogger->println(_pServer->arg("a"));
            UdpLogger.print(", ");
            UdpLogger.println(_pServer->arg("a"));
        }

        _pManager->DoCommand(action, resource);
//        _pUdpLogger->println(_pManager->GetStatus());
        UdpLogger.println(_pManager->GetStatus());

        _pServer->sendHeader("Location", String("/"), true);
        _pServer->send ( 302, "text/plain", "");
        // redirect...
    }

public:
    WebServer(Manager* pManager/*, UdpLogger* pUdpLogger*/)
    {
        _pManager = pManager;
       // _pUdpLogger = pUdpLogger;
        _pServer = new ESP8266WebServer(80);
        _pWebServer = this;
    }

    void Init()
    {
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());  //Print the local IP
 
        _pServer->on("/", handleMainPage);    //Associate the handler function to the path
        _pServer->on("/command", handleCommandStatic);
        _pServer->begin();                    //Start the server
        Serial.println("Server listening");
    }

    void Handle()
    {  
        _pServer->handleClient();         //Handling of incoming requests
    }

};

WebServer* WebServer::_pWebServer = 0;