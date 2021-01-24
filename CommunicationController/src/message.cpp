#include <Arduino.h>
#include "message.h"
#include <IridiumSBD.h>
#include <TinyGPS++.h>
#include <clock.h>

#define IridiumSerial Serial1
#define DIAGNOSTICS false // Change this to see diagnostics

struct GpsMessage
{
  uint8_t type; //1
  float longitude; //4
  float lattitude; //4
  int day;
  int month;
  int hour;
  int minute;
};

GpsMessage gpsMessage;

uint8_t buffer[200] = 
{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

IridiumSBD modem(IridiumSerial);
TinyGPSPlus gps;

//Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);
Message::Message()
{
  
}

void Message::SETUP()
{

  //gpsSerial.begin(9600); // Start the console serial port
  SerialUSB.begin(115200);
  while (!SerialUSB);

  IridiumSerial.begin(19200); // Start the serial port connected to the satellite modem

  SerialUSB.println("Starting modem..."); // Begin satellite modem operation

  
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("Begin failed: error ");
    SerialUSB.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      SerialUSB.println("No modem detected: check wiring.");
    return;
  }
}

void Message::printFirmwareRevision()
{
  char version[12];
  err = modem.getFirmwareVersion(version, sizeof(version));
  if (err != ISBD_SUCCESS)
  {
     SerialUSB.print("FirmwareVersion failed: error ");
     SerialUSB.println(err);
     return;
  }

  SerialUSB.print("Firmware Version is ");
  SerialUSB.print(version);
  SerialUSB.println(".");
}


void Message::sendGpsMessage(float lattitude, float longitude, int day, int month, int hour, int minute)
{
  gpsMessage = {1, lattitude, longitude, day, month, hour, minute};
  uint8_t* gps_bytes = reinterpret_cast<uint8_t*>(&gpsMessage);
  sendMessage(gps_bytes, sizeof(gpsMessage));
}

void Message::sendMessage(uint8_t* msg, size_t size)
{
  // Send the message
  SerialUSB.print("Trying to send the message.  This might take several minutes.\r\n");
  err = modem.getSignalQuality(signalQuality);
  
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("SignalQuality failed: error ");
    SerialUSB.println(err);
    return;
  }
  
  err = modem.sendSBDBinary(msg, size);
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("sendSBDText failed: error ");
    SerialUSB.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT)
      SerialUSB.println("Try again with a better view of the sky.");
  }
  else
  {
    SerialUSB.print("Message send ");
  }

  return;
}

void Message::getMessage()
{
  while(1)
  {
    static bool messageSent = false;
    int err;
  
    // Read/Write the first time or if there are any remaining messages
    if (!messageSent || modem.getWaitingMessageCount() > 0)
    {
      size_t bufferSize = sizeof(buffer);
  
      // First time through send+receive; subsequent loops receive only
      if (!messageSent)
        err = modem.sendReceiveSBDBinary(buffer, 11, buffer, bufferSize);
      else
        err = modem.sendReceiveSBDText(NULL, buffer, bufferSize);
        
      if (err != ISBD_SUCCESS)
      {
        SerialUSB.print("sendReceiveSBD* failed: error ");
        SerialUSB.println(err);
      }
      else // success!
      {
        messageSent = true;
        SerialUSB.print("Inbound buffer size is ");
        SerialUSB.println(bufferSize);
        SerialUSB.print("\"");
        for (int i=0; i<bufferSize; ++i)
        {
          if (isprint(buffer[i]))
          {
            SerialUSB.write(buffer[i]);
          }
        }
        
        SerialUSB.print("\"");
        SerialUSB.println();
        SerialUSB.print("Messages remaining to be retrieved: ");
        SerialUSB.println(modem.getWaitingMessageCount());
        break;
      }
    }
  }
}

void Message::getSignal()
{
  err = modem.getSignalQuality(signalQuality);
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("SignalQuality failed: error ");
    SerialUSB.println(err);
    return;
  }

  SerialUSB.print("On a scale of 0 to 5, signal quality is currently ");
  SerialUSB.print(signalQuality);
  SerialUSB.println(".");
}

Message msg = Message();
