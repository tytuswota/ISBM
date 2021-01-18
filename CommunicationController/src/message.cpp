#include <Arduino.h>
#include "message.h"
#include <IridiumSBD.h>
#include <TinyGPS++.h>

#define IridiumSerial Serial1
#define DIAGNOSTICS false // Change this to see diagnostics

uint8_t buffer[200] = 
{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

IridiumSBD modem(IridiumSerial);
TinyGPSPlus gps;

Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);


Message::Message()
{
}

void printHex(uint8_t num) 
{
  char hexChar[2];
  sprintf(hexChar, "%02X", num);
  SerialUSB.print(" ");
  SerialUSB.print(hexChar);
  SerialUSB.print(" ");
}

struct GpsMessage
{
  uint8_t type; //1
  float longitude; //4
  float lattitude; //4
};

void Message::SETUP()
{
  gpsSerial.begin(9600); // Start the console serial port
  SerialUSB.begin(115200);
  while (!SerialUSB);

  IridiumSerial.begin(19200); // Start the serial port connected to the satellite modem
  
  GpsMessage gps;

  gps.type = 1;
  gps.lattitude = 52.67452;
  gps.longitude = 4.67325;
  uint8_t* gps_bytes = reinterpret_cast<uint8_t*>(&gps);

  //int x = 650;
  //uint8_t highByte = x >> 8; // 138
  //uint8_t lowByte = x & 0xFF; // 2
  //int result = highByte << 8 | lowByte;

  SerialUSB.println("Starting modem..."); // Begin satellite modem operation
  
  for(int i = 0; sizeof(gps_bytes); i++)
  {
    printHex(gps_bytes[i]);
  }
  
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


String Message::intToHex(int myInt) 
{
  return String(myInt, HEX);
}


String Message::floatToHex(float myFloat) 
{
  long signed int myFloatHex = *(int32_t*)&myFloat;
  return String(myFloatHex, HEX);
}


String Message::stringToHex(String myString) 
{
  String myStringHex;
  uint8_t sizeOfString = myString.length() + 1;
  
  char buf[sizeOfString];
  myString.toCharArray(buf, sizeOfString);
  
  for (int i = 0; i < sizeof(buf) - 1; i++) {
    myStringHex += String(buf[i],HEX);
  }
  
  return myStringHex;
}


char* Message::string2char(String command)
{
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
} 


void Message::SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}


void Message::sendMessage(String msg)
{
  // Send the message
  SerialUSB.print("Trying to send the message.  This might take several minutes.\r\n");
  //err = modem.sendSBDText(string2char(stringToHex(msg)));
  uint8_t buf[msg.length()];
  
  msg.getBytes(buf, msg.length());
  
  err = modem.sendSBDBinary(buf, msg.length());
  //err = modem.sendSBDBinary(msg, sizeof(gps));
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("sendSBDText failed: error ");
    SerialUSB.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT)
      SerialUSB.println("Try again with a better view of the sky.");
  }
  else
  {
    SerialUSB.print("Message send: ");
    SerialUSB.println(stringToHex(msg));
  }
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


void Message::getGPSData()
{
  while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
       break;
      }
  }
  
  SerialUSB.println("lat: " + String(lattitude, 6));
  SerialUSB.println("long: " + String(longitude, 6));
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


#if DIAGNOSTICS
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}
#endif

Message msg = Message();
