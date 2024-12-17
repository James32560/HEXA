// #include <Arduino.h>
// #include <ArduinoJSON.h>
// #include "NimBLE.h"
// #include "Hexa.h"

// BLE ble;
// Hexa hexa;

// void RTBLEReceive(void *params)
// {
// 	while(true)
// 	{
// 		JsonDocument data = ble.receive();
// 		// hexa.width = data["width"].is<int>() ? data["width"].as<int>() : 0;
// 		// hexa.height = data["height"].is<int>() ? data["height"].as<int>() : 0;
// 		// hexa.duration = data["duration"].is<int>() ? data["duration"].as<int>() : 0;
// 		// hexa.gait = data["gait"].is<String>() ? data["gait"].as<String>() : "Stance";

// 		hexa.joyX = data["joyX"].is<float>() ? data["joyX"].as<float>() : 0;
// 		hexa.joyY = data["joyY"].is<float>() ? data["joyY"].as<float>() : 0;
// 		hexa.joyZ = data["joyZ"].is<float>() ? data["joyZ"].as<float>() : 0;
// 		hexa.duration = data["duration"].is<int>() ? data["duration"].as<int>() : 0;
// 		hexa.gait = data["gait"].is<String>() ? data["gait"].as<String>() : "Stance";

// 		vTaskDelay(10);
// 	}
// }

// void RTgaitTimer(void *params)
// {
// 	while(true)
// 	{
// 		static int startTick = xTaskGetTickCount();

// 		hexa.timer = (xTaskGetTickCount() - startTick);
// 		if(hexa.timer >= hexa.duration) hexa.timer = 0, startTick = xTaskGetTickCount();

// 		hexa.gaitGenerate();
		
// 		vTaskDelay(10);
// 	}
// }

// void setup()
// {
// 	Serial.begin(115200);

// 	int startTime = xTaskGetTickCount();
//     Serial.println("LUT init start");
// 	initLUT();
// 	Serial.println("LUT init end. Takes: " + String(xTaskGetTickCount() - startTime) + "ms");

// 	ble.begin(), hexa.begin();

// 	xTaskCreate
// 	(
// 		RTBLEReceive,
// 		"RTBLEReceive",
// 		2048,
// 		NULL,
// 		1,
// 		NULL
// 	);

// 	xTaskCreate
// 	(
// 		RTgaitTimer,
// 		"RTgaitTimer",
// 		16384,
// 		NULL,
// 		1,
// 		NULL
// 	);
// }

// void loop()
// {
// }

#include <Arduino.h>
#include <ArduinoJSON.h>
#include <HX711.h>

#include "NimBLE.h"

BLE ble;

const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;
HX711 scale;

float previousWeight = 0;
float weightThreshold = 1;

int stableTimer = 0;
int timertThreshold = 2000;
bool stable = true;

void setup()
{
	Serial.begin(115200);

	scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
	ble.begin();

	// Using for getting weight factor, which is -12134/56g=-216.678
	// scale.set_scale();
	// scale.tare();
	// Serial.println("HX711 0 weight value: " + String(scale.get_units(10)));
	// for(int i = 0; i < 10; i++)
	// {
	// 	Serial.println("Counting Down: " + String(10 - i));
	// 	delay(1000);
	// }
	// Serial.println("HX711 56g value: " + String(scale.get_units(10)));

	scale.set_scale(-216.678);
	scale.tare();
}

void loop()
{
	float currentWeight = scale.get_units(10);
	if(abs(currentWeight - previousWeight) > weightThreshold && stable)
	{
		stable = false, stableTimer = millis();
		Serial.println("Unstable");
	}
	else if(millis() - stableTimer > timertThreshold && !stable)
	{
		stable = true, previousWeight = currentWeight;
		Serial.println("Weight: " + String(currentWeight) + "g");
	}
}