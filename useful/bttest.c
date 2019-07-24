/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses call-backs on the event and RX so there's no data handling in the main loop!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

/**************************************************************************/
/*!
    This function is called whenever select ACI events happen
*/
/**************************************************************************/
void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or advertising timed out"));
      break;
    default:
      break;
  }
}

/**************************************************************************/
/*!
    This function is called whenever data arrives on the RX channel
*/
/**************************************************************************/
/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
  Serial.begin(9600);
  //while(!Serial); // Leonardo/Micro should wait for serial init
  //Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Callback Echo demo"));

  //uart.setRXcallback(rxCallback);
  //uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
void loop()
{
    uint8_t* i[4];
    i[0]='a';
    i[1]='b';
    i[2]='c';
  uart.write(i,4);
}