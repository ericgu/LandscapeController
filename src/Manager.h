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
        const static int TimeOut = 1000;        // in 10 millisecond units
        const static int DeviceCount = 5;

        Device* _devices[DeviceCount];

    public:

        Manager()
        {
            _devices[0] = new Device(GPIO4_D2_PUMP, "pump", "fountain", TimeOut);
            _devices[1] = new Device(GPI12_D6_BED, "bed", "lights", TimeOut);
            _devices[2] = new Device(GPI13_D7_HOUSE, "house", "lights", TimeOut);
            _devices[3] = new Device(GPI14_D5_UMBRELLA, "umbrella", "lights", TimeOut);
            _devices[4] = new OnIfAnyDevice(GPIO5_D1_12VPOWER, "12VPower", _devices[1], _devices[2], _devices[3]);

            for (int i = 0; i < DeviceCount; i++)
            {
                pinMode(_devices[i]->GetOutputPin(), OUTPUT);
            }
        }

        void DoCommand(Action& action, String& resource)
        {
            Serial.print("Action, resource: "); Serial.print(action.GetValue()); Serial.println(resource);

            // dispatch to all 
            for (int i = 0; i < DeviceCount; i++)
            {
                _devices[i]->DoAction(action, resource);
            }
        }

        String GetStatus()
        {
            String status;

            for (int i = 0; i < DeviceCount; i++)
            {
                status += _devices[i]->GetName() + ": " + _devices[i]->GetState() + ", ";
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