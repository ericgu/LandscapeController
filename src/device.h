#pragma once
//#include <String.h>
#include "action.h"

class Device
{
    private:
        String _group;
        bool _state;
        int _outputPin;
        int _timeout;
        int _timeoutRemaining;

    protected:
        String _name;

    public:
        Device() 
        {
            _state = false;
        }

        Device(int outputPin, String name, String group, int timeout)
        : Device()
        {
            _outputPin = outputPin;
            _name = name;
            _group = group;
            _timeout = timeout;
        }

        void SetState(bool newState)
        {
            if (newState)
            {
                _timeoutRemaining = _timeout;
            }
            else
            {
                _timeoutRemaining = 0;
            }
            _state = newState;
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
                    SetState(false);
                    break;

                case Action::On:
                    SetState(true);
                    break;

                case Action::Toggle:
                    SetState(!_state);
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

        void HandleTimeout()
        {
            if (_timeoutRemaining > 0)
            {
                _timeoutRemaining--;
            }
            else
            {
                if (_state)
                {
                    Serial.println("Timed out...");
                    SetState(false);
                }
            }
        }
};