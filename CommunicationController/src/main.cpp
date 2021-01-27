// Includes
#include <Arduino.h>
#include "message.h"
#include <gps.h>
#include <clock.h>
#include <IridiumSBD.h>
#include <SPI.h>
#include "wiring_private.h" // pinPeripheral() function

int alarmMonth, alarmDay, alarmHour, alarmMinute;
bool alarmIsSet = false; // Boolean for the alarm

// Serial communication for the GPS module
Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);

#define CS_PIN 6 // CAN-bus SPI pin 
#define SEND_MSG_MINUTE_TIME 5 // Time to send a message

// Serial communication for CAN-bus
SPIClass SPI2 (&sercom2, 3, 5, 4, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_1); // D3-MISO, D4-MOSI, D5-SCK

// Setup
void setup() {
  gpsSerial.begin(9600);
  gps.SETUP();
  msg.SETUP(); 
  msg.printFirmwareRevision();
  SPI2.begin();

  // Setup all pins and SPI ports
  pinPeripheral(3, PIO_SERCOM_ALT);
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(5, PIO_SERCOM);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Make sure it is high to start
  SPI2.setClockDivider(SPI_CLOCK_DIV128); // Slowdown the master
}

// Open a serial communication for the GPS 
void SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}

// Call the GPS module
void gpsCall()
{
  float lattitude;
  float longitude;
  int day;
  int month;
  int hour;
  int minute;
  gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);
  
  // Print debug
  // SerialUSB.println("lat: " + String(lattitude, 6));
  // SerialUSB.println("long: " + String(longitude, 6));
}

// Alarm to send GPS location on specific time
void setAlarm(int minutes)
{
  SerialUSB.print("Alarm was set:");
  // Sync the alarm time with the clock
  clock.getDateTime(alarmMonth, alarmDay, alarmHour, alarmMinute); 
      
  // Add the minutes to the alarm time
  alarmMinute += minutes;

  // If the minutes are bigger than 60 than the time is changed to hours
  if (alarmMinute > 59)  
  {
    alarmHour += alarmMinute / 60 % 24;
    alarmMinute %= 60;
  }

  gpsCall();
  
  alarmIsSet = true;
}

void loop() 
{
  //digitalWrite(CS_PIN, LOW);// Select can bus
  //SPI2.transfer('a');//Setting character
  //digitalWrite(CS_PIN, HIGH);// Deselect can bus
  
  // Check if the alarm is set to true
  if(alarmIsSet) 
  {
    // If the alarm time is equal to the current time set the alarm on
    if(clock.alarmHasMatch(alarmHour, alarmMinute))       
    {
      SerialUSB.print("ALARM OM: ");
      SerialUSB.print(alarmHour + " : " + alarmMinute);
      alarmIsSet = false;
      
      float lattitude, longitude;
      int day, month, hour, minute;

      // Get the GPS location and time
      gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);

      // Send a message with the GPS location and time
      msg.sendGpsMessage(lattitude, longitude, day, month, hour, minute);
      setAlarm(SEND_MSG_MINUTE_TIME);
    }
  }
  
  // Check if there is a order
  if(!msg.orders)
  {
    setAlarm(SEND_MSG_MINUTE_TIME);
    SerialUSB.println("Waiting for orders...");
    SerialUSB.println("give user input!");
    
    msg.orders = true;
  }

  // Give input via serial
  if(SerialUSB.available() > 0)
  {
    String input = SerialUSB.readString();
    input.trim();

    // Request the signal strength from the ISBD module
    if((input == "get signal") || (input == "sig")) 
    {
      SerialUSB.println("user input:" + input);
      msg.getSignal();
      msg.orders = false;
    }
    
    // Request current longitude and lattitude from GPS module
    if((input == "gps")) 
    {
      SerialUSB.println("user input:" + input);
      float lattitude;
      float longitude;
      int day;
      int month;
      int hour;
      int minute;
      gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);

      SerialUSB.println("lat: " + String(lattitude, 6));
      SerialUSB.println("long: " + String(longitude, 6));
      
      msg.orders = false;
    }

    // Request the time and date from the GPS module
    if((input == "time"))
    {
      SerialUSB.println("user input:" + input);
      clock.showDateTime();
      msg.orders = false;
    }
    
    // Download MT message to the ISBD 
    // REQUIRES LINE-OF-SIGHT VIEW TO SATELLITE
    if((input == "get msg"))
    {
      SerialUSB.println("user input:" + input);
      msg.getMessage();
      msg.orders = false;
    }
  
    // Send MO message to Iridium Gateway
    if((input == "send gps msg"))
    {
      SerialUSB.println("user input:" + input);
      float lattitude, longitude;
      int day, month, hour, minute;
      gps.getLattitudeLongitude(gpsSerial, lattitude, longitude, day, month, hour, minute);
      msg.sendGpsMessage(lattitude, longitude, day, month, hour, minute);
      msg.orders = false;
    }

    // Set the alarm to a specific time
    if((input == "set alarm"))
    {
      SerialUSB.println("Om de hoeveel minuten moet het alarm afgaan?");
      String alarmMinutes = "";
      
      while (alarmMinutes.equals(""))
      {
        alarmMinutes = SerialUSB.readString();
      }

      setAlarm(alarmMinutes.toInt());
      
      msg.orders = false;
    }
  }
}