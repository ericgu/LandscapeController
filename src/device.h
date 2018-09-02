#pragma once
//#include <String.h>
#include "action.h"

class Device
{
    private:
        String _group;
        bool _state;
        int _outputPin;

    protected:
        String _name;

    public:
        Device() 
        {
            _state = false;
        }

        Device(int outputPin, String name, String group)
        : Device()
        {
            _outputPin = outputPin;
            _name = name;
            _group = group;
        }

        void DoAction(Action& action, String& name)
        {
            //Serial.print("Matching: "); Serial.println(_name);
            //Serial.println(name);
            //Serial.println(action.GetValue());

            if (name != _name && name != _group)
            {
                return;
            }

            switch (action.GetValue())
            {
                case Action::Off:
                    _state = false;
                    break;

                case Action::On:
                    _state = true;
                    break;

                case Action::Toggle:
                    _state = !_state;
                    break;
            }
            //Serial.println(_state);
        }

        virtual bool GetState()
        {
            return _state;
        }

        String GetName()
        {
            return _name;
        }

        int GetOutputPin()
        {
            return _outputPin;
        }
};