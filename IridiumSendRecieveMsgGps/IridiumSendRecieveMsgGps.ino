#include <Arduino.h>
#include <TinyGPS++.h>

#include <IridiumSBD.h>

//-------------------Includes-------------------//
#include "Arduino.h"
#include <Message.h>


#define IridiumSerial Serial1
#define DIAGNOSTICS false // Change this to see diagnostics

// Declare the IridiumSBD object
float lattitude, longitude; 
int signalQuality = -1;
int err;
bool orders = false;

IridiumSBD modem(IridiumSerial);
TinyGPSPlus gps;

Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);

uint8_t buffer[200] = 
{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

String intToHex(int myInt) {
  return String(myInt, HEX);
}

String floatToHex(float myFloat) {
  long signed int myFloatHex = *(int32_t*)&myFloat;
  return String(myFloatHex, HEX);
}

String stringToHex(String myString) {
  String myStringHex;
  uint8_t sizeOfString = myString.length() + 1;
  
  char buf[sizeOfString];
  myString.toCharArray(buf, sizeOfString);
  
  for (int i = 0; i < sizeof(buf) - 1; i++) {
    myStringHex += String(buf[i],HEX);
  }
  
  return myStringHex;
}

void SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}

void setup()
{
  msg.SETUP(); 
  msg.printFirmwareRevision();
}


//-------------------Main-------------------//
void loop()
{
  if (!msg.orders)                                        // waiting for user input
  {
    SerialUSB.println("Waiting for orders...");
    SerialUSB.println("give user input!");
    msg.orders = true;
  }
  
  if(SerialUSB.available() > 0)                       // read from serial usb. Type one of the following commands into Serial Monitor:
  {
    String input = SerialUSB.readString();
    input.trim();

    if((input == "get signal") || (input == "sig"))   // 'get signal' to request signal strength from ISBD module
    {
      SerialUSB.println("user input:" + input);
      msg.getSignal();
      msg.orders = false;
    }
    
    if((input == "gps"))                              // 'gps' to request current longitude and lattitude from GPS module
    {
      SerialUSB.println("user input:" + input);
      msg.getGPSData();
      msg.orders = false;
    }
    
    if((input == "get msg"))                          // 'get msg' to download the first MT (Mobile Terminated) msgage to ISBD module *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      msg.getMessage();
      msg.orders = false;
    }
    
    if((input == "send gps msg"))                     // 'send gps msg' to send MO (Mobile Originated) message to Iridium Gateway *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      msg.getGPSData();
      //String msg = "1;" + String(msg.lattitude,6) + ";" + String(msg.longitude,6);
      //msg.sendMessage(msg);
      //msg.orders = false;
    }
  } 
}
