
#include "SoftwareSerial.h"
#include "Seeed_Fingerprint.h"

Fingerprint fingerprint(2, 3);

void setup()  
{
	Serial.begin(115200);
	Serial.println("Fingerprint test");  

	if(fingerprint.Init())
	{
		Serial.println("Found fingerprint sensor!");
	}
	else
	{
		Serial.println("Did not find fingerprint sensor :(");
		while(1);
	}
	
	Serial.println("Waiting for valid finger...");
}

void loop()
{
	int key_value;
	int id_value;
	
	key_value = task_uart_key();
	if(key_value < 9999 && key_value > 0)
	{
		fingerprint.FingerprintWrite(key_value);
	}
	
	id_value = fingerprint.FingerprintRead();
	if(id_value >= 0)
	{
		Serial.print("Read fingerprint id: ");
		Serial.println(id_value);
	}
	Serial.println("sys loop.");
	delay(1000);
}

unsigned int task_uart_key()
{
    String inString = "";
    unsigned int keyValue = 0;
    unsigned char bitCount = 0; 
    unsigned char dataTemp1[10] = {0};
    while(Serial.available() > 0)
    {
            unsigned char inChar = Serial.read();
            inString += (char)inChar;
            dataTemp1[bitCount] = inChar - '0';
            bitCount += 1;
            delay(10);
    }
    if(inString != "")
    {
            if(bitCount > 4)
            {
                Serial.println("Key input error.");
            }
            else
            {
                    for(char i=0;i<bitCount;i++)
                    {
                            unsigned int dataTemp2 = 1;
                            for(char j=0;j<(bitCount-i-1);j++)dataTemp2 *= 10;
                            keyValue += (dataTemp1[i] * dataTemp2);
                    }   
                    Serial.print("Key value is: ");
                    Serial.println(keyValue); 
            }
    }
    return keyValue;   
}
