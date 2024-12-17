#include <NimBLE.h>

NimBLEAdvertising *BLE::advertising;
bool BLE::connection = false;

void BLE::CallBacks::onConnect(NimBLEServer *server)
{
    Serial.println("Connected");
    BLE::connection = true;
}

void BLE::CallBacks::onDisconnect(NimBLEServer *server)
{
    Serial.println("Connection Lost");
    BLE::connection = false;
    advertising->start();
}

void BLE::begin()
{
    NimBLEDevice::init("ESP32-BLE");

    NimBLEServer *server = NimBLEDevice::createServer();
    server->setCallbacks(new CallBacks());
    
    NimBLEService *service = server->createService(SERVICE_UUID);
    characteristic = service->createCharacteristic
    (
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ   |
        NIMBLE_PROPERTY::WRITE  |
        NIMBLE_PROPERTY::NOTIFY
    );
    characteristic->addDescriptor(new NimBLE2904());
    service->start();

    advertising = NimBLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->start();
}

void BLE::send(JsonDocument& jsonData)
{
    if (connection)
    {
        String data;
        serializeJson(jsonData, data);
        characteristic->setValue(data);
        characteristic->notify();
    }
}

JsonDocument BLE::receive()
{
    JsonDocument data;

    if(connection)
    {
        String received = this->characteristic->getValue();
        deserializeJson(data, received);
    }
    else
    {
        data["error"] = "No connection";
    }

    return data;
}