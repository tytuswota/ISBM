#include <Arduino.h>
#include "message.h"
#include <gps.h>
#include <clock.h>

int alarmMonth, alarmDay, alarmHour, alarmMinute;
bool alarmIsSet = false;

Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);


#include <SPI.h>
#include "wiring_private.h" // pinPeripheral() function
#define CSPIN 6
#define Time 25

//D3-MISO, D4-MOSI, D5-SCK
SPIClass SPI2 (&sercom2, 3, 5, 4, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_1); 

void setup() {
  gpsSerial.begin(9600);
  gps.SETUP();
  msg.SETUP(); 
  msg.printFirmwareRevision();

  //Get all pins and SPI ports setup
  SPI2.begin();
  pinPeripheral(3, PIO_SERCOM_ALT);
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(5, PIO_SERCOM);
  pinMode(CSPIN, OUTPUT);
  digitalWrite(CSPIN, HIGH); //make sure it is high to start
  SPI2.setClockDivider(SPI_CLOCK_DIV128); //Slow down the master a bit
}

void SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}

void loop() 
{
  //digitalWrite(CSPIN, LOW);// Select can bus
  //SPI2.transfer('a');//Setting character
  //digitalWrite(CSPIN, HIGH);// Deselect can bus
  
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

    if((input == "set alarm"))
    {
      SerialUSB.println("Om de hoeveel minuten moet het alarm afgaan?");
      String alarmMinutes = SerialUSB.readString();
      clock.getDateTime(alarmMonth, alarmDay, alarmHour, alarmMinute);    // hier worde de alarmtijd gesynced met de clock
      
      alarmMinute += alarmMinutes.toInt();                                // hier word het aantal minuten opgeteld bij de alarmtijd
      if(alarmMinute > 59)                                                // als aantal minuten groter is dan 60 word het omgezet in aantal uren en minuten
      {
        alarmHour +=  alarmMinute / 60;
        alarmMinute %=  60;
      }
      
      alarmIsSet = true;
    }
  }

  if(alarmIsSet)                                                          // alleen als er een alarm is gezet wordt deze if statement aangeroepen
  {
    if(clock.alarmHasMatch(alarmHour, alarmMinute))                       // als de alarm tijd overeenkomt met huidige tijd -> alarm gaat af
    {
      SerialUSB.print("ALARM OM: ");
      SerialUSB.print(alarmHour);
      SerialUSB.print(":");
      SerialUSB.print(alarmMinute);
      alarmIsSet = false;
    }
  }
}