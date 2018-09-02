class HardWiredController
{
    const int StateReady = 1;             // no button press detected.
    const int StateWaitingToSettle = 2;   // button pressed, waiting to make sure we have the right one
    const int StateWaitingForOff = 3;     // waiting until we no longer detect a button pressed
    const int StateWaitingToEnd = 4;      // wait to make sure there is no bounce.

    Manager* _pManager;
    String _lastResource;
    int _pauseCount;
    int _state;

public:
    HardWiredController(Manager* pManager)
    {
        _pManager = pManager;
        _pauseCount = 0;
        _state = StateReady;
    }

    String GetButton()
    {
      int value = analogRead(A0);

      //Serial.print("Analog: ");
      //Serial.println(value);

      // Thresholds:
      //    0 - 127  off
      //  128 - 382  button 1
      //  383 - 637  button 2
      //  638 - 892  button 3
      //  893 -1020  button 4

      String resource;

      if (value < 127)
      {
        resource = "";
      }
      else if (value < 383)
      {
        resource = "pump";
      }
      else if (value < 638)
      {
        resource = "bed";
      }
      else if (value < 893)
      {
        resource = "house";
      }
      else
      {
        resource = "umbrella";
      }

      if (resource != "")
      {
        //Serial.print(value); Serial.print(" "); Serial.println(resource);
      }

      return resource;
    }

    void Handle()
    {
      // Sense analog input and send appropriate command if there is a value there.

      String resource = GetButton();
      //Serial.print(_state); Serial.print(" "); Serial.println(resource);

      if (_state == StateReady)
      {
        if (resource != "") // a button was pressed. 
        {
          Serial.print("StateWaitingToSettle: "); Serial.println(resource);
          _state = StateWaitingToSettle;
          _pauseCount = 10;
        }
      }
      else if (_state == StateWaitingToSettle)
      {
        if (_pauseCount > 0)
        {
          _pauseCount--;
          return;
        }

        Serial.print("Toggle resource:"); Serial.println(resource);
        Action action("toggle");
        //_pManager->DoCommand(action, resource);
        _state = StateWaitingForOff;        
      }
      else if (_state == StateWaitingForOff)
      {
        if (resource == "")
        {
          Serial.print("waiting to end");
          _state = StateWaitingToEnd;      
          _pauseCount = 10;  
        }
      }
      else if (_state == StateWaitingToEnd)
      {
        if (_pauseCount > 0)
        {
          _pauseCount--;
          return;
        }

        Serial.print("Ready");
        _state = StateReady;
      }
  }

};