/*
In HM10
Receiver- 2
Transmitter - 3
In nRF
MISO (I think receiver)-12
MOSI (I think transmitter)-11
thus, to make a bt port, replace 2 with 12 and 3 with 11 
 */
#include <SoftwareSerial.h>

//SoftwareSerial SerialBt(2, 3);
SoftwareSerial SerialBt(12, 11);
void setup()
{
    Serial.begin(9600);
    SerialBt.begin(9600);
}

void loop()
{
    if (SerialBt.available()) {
        Serial.write(SerialBt.read());
    }

    if (Serial.available()) {
        SerialBt.write(Serial.read());
    }
}