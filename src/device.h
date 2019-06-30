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
        int _pwmLevel;

         int PwmValues[5] = {205, 410, 614, 819, 1023};

    protected:
        String _name;

    public:
        Device() 
        {
            _state = false;
            _pwmLevel = 1023;
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
            UdpLogger.print(_name);
            UdpLogger.print(" new state: ");
            UdpLogger.println(newState);
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

                case Action::Dim20:
                case Action::Dim40:
                case Action::Dim60:
                case Action::Dim80:
                case Action::Dim100:
                    _pwmLevel = PwmValues[action.GetValue() - Action::Dim20];
                    Serial.print("Pwm at: "); Serial.println(_pwmLevel);
                    break;

            }
            //Serial.println(_state);
        }

        void UpdateState()
        {
            int state = GetState();
            Serial.println(state);
            Serial.println(_pwmLevel);

            if (state)
            {
                analogWrite(_outputPin, _pwmLevel);
            }
            else
            {
                analogWrite(_outputPin, 0);
            }
        }

        virtual bool GetState()
        {
            return _state;
        }

        void SetAsOutputPin()
        {
            pinMode(_outputPin, OUTPUT);
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

        String GetStateString()
        {
            return _name + ": " + GetState() + " => " + _pwmLevel;
        }
};