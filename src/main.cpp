#include <Arduino.h>
#include <WiFi.h>
#include <FlowSensor.h>

// Pin Declaration
#define FlowSensor1 2
#define FlowSensor2 3 
#define FlowSensor3 4
#define FlowSensor4 5

// Flow Sensor Declaration
FlowSensor Sensor1(YFS401, FlowSensor1);
FlowSensor Sensor2(YFS401, FlowSensor2);
FlowSensor Sensor3(YFS401, FlowSensor3);
FlowSensor Sensor4(YFS401, FlowSensor4);

unsigned long timeprev, timeprint;

// Interrupt Service Routine
void IRAM_ATTR count1()
{
	Sensor1.count();
}

void IRAM_ATTR count2()
{
	Sensor2.count();
}

void IRAM_ATTR count3()
{
	Sensor3.count();
}

void IRAM_ATTR count4()
{
	Sensor4.count();
}

void setup()
{
	Serial.begin(115200);

	// Sensor begin (Interrupt)
	Sensor1.begin(count1);
	Sensor2.begin(count2);
	Sensor3.begin(count3);
	Sensor4.begin(count4);
}

void loop()
{
	unsigned long now = millis();

	// Sensor calculated data every 1 sec
	if (now - timeprev >= 1000)
	{
		Sensor1.read();
		Sensor2.read();
		Sensor3.read();
		Sensor4.read();

		timeprev = now;
	}

	// print data every 1 min
	if (now - timeprint >= 60000)
	{
		Serial.println("Volume (L)");
		Serial.print("Flow Sensor 1 : ");
		Serial.println(Sensor1.getVolume());
		Serial.print("Flow Sensor 2 : ");
		Serial.println(Sensor2.getVolume());
		Serial.print("Flow Sensor 3 : ");
		Serial.println(Sensor3.getVolume());
		Serial.print("Flow Sensor 4 : ");
		Serial.println(Sensor4.getVolume());
		Serial.println("");
		Serial.println("Flow Rate (L/m)");
		Serial.print("Flow Sensor 1 : ");
		Serial.println(Sensor1.getFlowRate_m());
		Serial.print("Flow Sensor 2 : ");
		Serial.println(Sensor2.getFlowRate_m());
		Serial.print("Flow Sensor 3 : ");
		Serial.println(Sensor3.getFlowRate_m());
		Serial.print("Flow Sensor 4 : ");
		Serial.println(Sensor4.getFlowRate_m());
		Serial.println("");
		Serial.println("");
	}
}