class StairSensing
{
    static const int STAIR_SENSE_PIN = 16;

    bool stairLightsOn = false;
    Manager* _pManager;

public:
    StairSensing(Manager* pManager)
    {
        _pManager = pManager;
        pinMode(STAIR_SENSE_PIN, INPUT);
    }

    void SetHouseLights(char* actionString)
    {
        Serial.print("House lights: "); Serial.println(actionString);

        String a = String(actionString);
        Action action(a);
        String resource("house");
        _pManager->DoCommand(action, resource); 
    }

    void Handle()
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
};