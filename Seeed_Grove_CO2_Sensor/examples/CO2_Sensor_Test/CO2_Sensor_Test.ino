// test for seeed match UP project
// JY.W @ 2016-01-04

#include <SoftwareSerial.h>
#include "Seeed_CO2.h"

#define GET_TEMP_CMD	0
#define GET_CO2PPM_CMD	1

CO2 co2(2, 3);

void setup()
{
	Serial.begin(115200);
	Serial.println("Test for Seeed match UP project");
	Serial.println("CO2 Sensor");
	
	co2.Init();
}

void loop()
{	
	int temperature_value;
	int co2ppm_value;
	
	temperature_value = co2.Read(GET_TEMP_CMD);
	co2ppm_value = co2.Read(GET_CO2PPM_CMD);
	
	Serial.print("Temperature is ");
	Serial.print(temperature_value);
	Serial.print("\t");
	Serial.print("co2ppm is ");
	Serial.print(co2ppm_value);
	Serial.println(" ");
	
	delay(1000);
}
