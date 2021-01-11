//-------------------Includes-------------------//
#include "Arduino.h"
#include <Message.h>


//-------------------Setup-------------------//
void setup()
{
  mess.SETUP(); 
  mess.printFirmwareRevision();
}


//-------------------Main-------------------//
void loop()
{
  if (!mess.orders)                                        // waiting for user input
  {
    SerialUSB.println("Waiting for orders...");
    SerialUSB.println("give user input!");
    mess.orders = true;
  }
  
  if(SerialUSB.available() > 0)                       // read from serial usb. Type one of the following commands into Serial Monitor:
  {
    String input = SerialUSB.readString();
    input.trim();

    if((input == "get signal") || (input == "sig"))   // 'get signal' to request signal strength from ISBD module
    {
      SerialUSB.println("user input:" + input);
      mess.getSignal();
      mess.orders = false;
    }
    
    if((input == "gps"))                              // 'gps' to request current longitude and lattitude from GPS module
    {
      SerialUSB.println("user input:" + input);
      mess.getGPSData();
      mess.orders = false;
    }
    
    if((input == "get msg"))                          // 'get msg' to download the first MT (Mobile Terminated) message to ISBD module *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      mess.getMessage();
      mess.orders = false;
    }
    
    if((input == "send gps msg"))                     // 'send gps msg' to send MO (Mobile Originated) message to Iridium Gateway *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      mess.getGPSData();
      String msg = "1;" + String(mess.lattitude,6) + ";" + String(mess.longitude,6);
      mess.sendMessage(msg);
      mess.orders = false;
    }
  } 
}
