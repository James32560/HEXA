#include <NimBLEDevice.h>
#include <ArduinoJson.h>

#define SERVICE_UUID        "0000ffe0-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID "0000ffe1-0000-1000-8000-00805f9b34fb"

class BLE
{
public:
    static bool connection;

    void begin();
    void send(JsonDocument& jsonData);
    JsonDocument receive();

private:
    static BLEAdvertising *advertising;

    BLECharacteristic *characteristic;

    class CallBacks: public BLEServerCallbacks
    {
        void onConnect(BLEServer *server) override;
        void onDisconnect(BLEServer *server) override;
    };
};