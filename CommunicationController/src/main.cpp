#include <Arduino.h>
#include "message.h"
#include <gps.h>
#include <clock.h>

Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);

void setup() {
  gpsSerial.begin(9600);
  gps.SETUP();
  msg.SETUP(); 
  msg.printFirmwareRevision();
}

void SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}

void loop() 
{
  
  if(!msg.orders)
  {
    SerialUSB.println("Waiting for orders...");
    SerialUSB.println("give user input!");
    msg.orders = true;
  }

  if(SerialUSB.available() > 0)
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
      float lattitude;
      float longitude;
      int day;
      int month;
      int hour;
      int minute;
      SerialUSB.println("in the getgps function");
      gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);

      SerialUSB.println("lat: " + String(lattitude, 6));
      SerialUSB.println("long: " + String(longitude, 6));
      
      msg.orders = false;
    }

    if((input == "time"))                          // 'get msg' to download the first MT (Mobile Terminated) message to ISBD module *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      clock.showDateTime();
      msg.orders = false;
    }
    
    if((input == "get msg"))                          // 'get msg' to download the first MT (Mobile Terminated) message to ISBD module *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      msg.getMessage();
      msg.orders = false;
    }

    if((input == "send msg"))                          // 'get msg' to download the first MT (Mobile Terminated) message to ISBD module *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      //msg.sendMessage("a");
      msg.orders = false;
    }
  
    if((input == "send gps msg"))                     // 'send gps msg' to send MO (Mobile Originated) message to Iridium Gateway *REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE*
    {
      SerialUSB.println("user input:" + input);
      float lattitude;
      float longitude;
      int day;
      int month;
      int hour;
      int minute;
      gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);
      msg.sendGpsMessage(lattitude, longitude, day, month, hour, minute);
      msg.orders = false;
    }
  }
}