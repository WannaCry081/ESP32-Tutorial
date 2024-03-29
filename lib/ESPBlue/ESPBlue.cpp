#include "ESPBlue.hpp"

ESPBlue::ESPBlue(const String &serviceUUID, const String &characteristicUUID)
    : _serviceUUID(serviceUUID), _characteristicUUID(characteristicUUID)
{
}

void ESPBlue::Setup()
{
    const char *SERVICE_UUID = _serviceUUID.c_str();
    const char *CHARACTERISTIC_UUID = _characteristicUUID.c_str();

    BLEDevice::init("ESP32_BLE");

    BLEServer *pServer = BLEDevice::createServer();

    BLEService *pService = pServer->createService(SERVICE_UUID);
    _pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    _pCharacteristic->setCallbacks(nullptr);

    pService->start();
    pServer->getAdvertising()->start();
}

void ESPBlue::SetCallbacks(BLECharacteristicCallbacks *callbacks)
{
    if (callbacks == nullptr)
    {
        return;
    }

    _pCharacteristic->setCallbacks(callbacks);
}

// This method is called when the central device writes a new value to the characteristic.
void SampleCallback::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string value = pCharacteristic->getValue();

    // Sample code for LED on and off
    if (value.length() > 0)
    {
        Serial.println("Received Value: " + String(value.c_str()));
        if (value[0] == 0x01)
        {
            digitalWrite(2, HIGH);
        }
        else if (value[0] == 0x00)
        {
            digitalWrite(2, LOW);
        }
    }
}

// This method is called when a central device requests to read the value of the characteristic.
void SampleCallback::onRead(BLECharacteristic *pCharacteristic)
{
}

// This method is called when the characteristic sends a notification.
void SampleCallback::onNotify(BLECharacteristic *pCharacteristic)
{
}

// This method is called when there is a status change in the characteristic.
void SampleCallback::onStatus(BLECharacteristic *pCharacteristic, Status s, uint32_t code)
{
}

// This method is called when the characteristic sends an indication.
void SampleCallback::onIndicate(BLECharacteristic *pCharacteristic)
{
}
