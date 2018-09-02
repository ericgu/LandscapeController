#pragma once
#include <String.h>
#include "action.h"
#include "device.h"

class OnIfAnyDevice: public Device
{
    private:
        Device* _pFirst;
        Device* _pSecond;
        Device* _pThird;

    public:
        OnIfAnyDevice() 
        {
        }

        OnIfAnyDevice(int outputPin, String name, Device* pFirst, Device* pSecond, Device* pThird)
        : Device(outputPin, name, "")
        {
            _pFirst = pFirst;
            _pSecond = pSecond;
            _pThird = pThird;
        }

        virtual bool GetState()
        {
            return _pFirst->GetState() || _pSecond->GetState() || _pThird->GetState();
        }
};