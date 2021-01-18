//-------------------Includes-------------------//
#include "Arduino.h"
#include <Message.h>


//-------------------Setup-------------------//
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
      String msg = "1;" + String(msg.lattitude,6) + ";" + String(msg.longitude,6);
      msg.sendMessage(msg);
      msg.orders = false;
    }
  } 
}
