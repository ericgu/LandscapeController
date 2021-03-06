#pragma once

#include "device.h"
#include "OnIfAnyDevice.h"

#define GPIO4_D2_PUMP 4
#define GPIO5_D1_12VPOWER 5
#define GPI12_D6_BED 12
#define GPI13_D7_HOUSE 13
#define GPI14_D5_UMBRELLA 14

class Manager
{
    private:
        const static int PumpTimeOut = 100 * 60 * 4;        // in 10 millisecond units - 4 hours
        const static int LightTimeOut = 100 * 60 * 2;       // in 10 millisecond units - 2 hours
        const static int DeviceCount = 5;

        Device* _devices[DeviceCount];

    public:

        Manager()
        {
            _devices[0] = new Device(GPIO4_D2_PUMP, "pump", "fountain", PumpTimeOut);
            _devices[1] = new Device(GPI12_D6_BED, "bed", "lights", LightTimeOut);
            _devices[2] = new Device(GPI13_D7_HOUSE, "house", "lights", LightTimeOut);
            _devices[3] = new Device(GPI14_D5_UMBRELLA, "umbrella", "lights", LightTimeOut);
            _devices[4] = new OnIfAnyDevice(GPIO5_D1_12VPOWER, "12VPower", _devices[1], _devices[2], _devices[3]);

            for (int i = 0; i < DeviceCount; i++)
            {
                _devices[i]->SetAsOutputPin();
            }
        }

        void DoCommand(Action& action, String& resource)
        {
            Serial.print("Action, resource: "); Serial.print(action.GetValue()); Serial.println(resource);

            // dispatch to all 
            for (int i = 0; i < DeviceCount; i++)
            {
                _devices[i]->DoAction(action, resource);
                _devices[i]->UpdateState();
            }
        }

        String GetStatus()
        {
            String status;

            for (int i = 0; i < DeviceCount; i++)
            {
                status += _devices[i]->GetStateString() + ", ";
            }

            return status;
        }

        void HandleTimeout()
        {
            for (int i = 0; i < DeviceCount; i++)
            {
                _devices[i]->HandleTimeout();
            }
        }
};