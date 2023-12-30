#include "ESPWifi.hpp"

ESPWifi::ESPWifi(String &ssid, String &password) : _ssid(ssid), _password(password)
{   
    WiFi.begin(_ssid, _password);
}

bool ESPWifi::IsConnect()
{
    return WiFi.status() != WL_CONNECTED;
}
