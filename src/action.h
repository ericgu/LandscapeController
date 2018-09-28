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
        static const int Dim20 = 4;
        static const int Dim40 = 5;
        static const int Dim60 = 6;
        static const int Dim80 = 7;
        static const int Dim100 = 8;

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
            else if (action ==  "dim20")
            {
                _value = Dim20;
            }
            else if (action ==  "dim40")
            {
                _value = Dim40;
            }
            else if (action ==  "dim60")
            {
                _value = Dim60;
            }
            else if (action ==  "dim80")
            {
                _value = Dim80;
            }
            else if (action ==  "dim100")
            {
                _value = Dim100;
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