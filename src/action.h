#pragma once

#include <String.h>

class Action
{
    private:
        int _value;

    public:
        static const int On = 1;
        static const int Off = 2;
        static const int Toggle = 3;

        Action() {
            _value = 0;
        }

        Action(String action)
        {
            if (action == "on")
            {
                _value = On;
            }     
            else if (action ==  "off")
            {
                _value = Off;
            }     
            else if (action ==  "toggle")
            {
                _value = Toggle;
            }
            else
            {
                _value = 0;
            }     
        }

        int GetValue()
        {
            return _value;
        }
};