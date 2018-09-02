#include "EEPROM.h"

typedef unsigned char byte;

class PersistentStorage
{
  public:

    char _ssid[33];
    char _password[65];

    PersistentStorage()
    {
      memset(this, 0, sizeof(PersistentStorage));
	  }

    void Save()
    {
      EEPROM.begin(4096);
      byte* pData = (byte*) this;
      for (int i = 0; i < sizeof(PersistentStorage); i++)
      {
        EEPROM.write(i, *pData);
        pData++;
      }
      
      EEPROM.commit();
      Serial.println("Saved configuration");
    }

    void Load()
    {
      Serial.println("Load");
      EEPROM.begin(4096);

      byte* pStart = (byte*) this;
      byte* pData = pStart;
      int size = sizeof(PersistentStorage);
      for (int i = 0; i < size; i++)
      {
        *pData = EEPROM.read(i);
        pData++;
      }      
    }

    void SsidSet(String ssid)
    {
      strcpy(_ssid, ssid.c_str());
    }

    String SsidGet()
    {
      return String(_ssid);
    }
  
    void PasswordSet(String password)
    {
      strcpy(_password, password.c_str());
    }

    String PasswordGet()
    {
      return String(_password);
    }
};


