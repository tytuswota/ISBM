#include <IridiumSBD.h>
#include <TinyGPS++.h>

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

void SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}

void setup()
{
  // Start the console serial port
  gpsSerial.begin(9600);
  SerialUSB.begin(115200);
  while (!SerialUSB);

  // Start the serial port connected to the satellite modem
  IridiumSerial.begin(19200);

  // Begin satellite modem operation
  SerialUSB.println("Starting modem...");
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    SerialUSB.print("Begin failed: error ");
    SerialUSB.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      SerialUSB.println("No modem detected: check wiring.");
    return;
  }

  // Example: Print the firmware revision
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

void sendMessage(String msg)
{
  // Send the message
  SerialUSB.print("Trying to send the message.  This might take several minutes.\r\n");
  
  err = modem.sendSBDText(string2char(msg));
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
    SerialUSB.println(msg);
  }
}

void getAllMessages()
{
  while(1){
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

void getGPSData()
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

void getSignal()
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

void loop()
{
  if (!orders) {
    SerialUSB.println("Waiting for orders...");
    SerialUSB.println("give user input!");
    orders = true;
  }
  
  //read from serial usb
  if(SerialUSB.available() > 0)
  {
    String input = SerialUSB.readString();
    
    input.trim();

    if((input == "get signal") || (input == "sig"))
    {
      SerialUSB.println("user input:" + input);
      getSignal();
      orders = false;
    }
    
    if((input == "gps"))
    {
      SerialUSB.println("user input:" + input);
      getGPSData();
      orders = false;
    }
    
    if((input == "get msg"))
    {
      SerialUSB.println("user input:" + input);
      getAllMessages();
      orders = false;
    }
    
    if((input == "send gps msg"))
    {
      SerialUSB.println("user input:" + input);
      getGPSData();
      String msg = "1;" + String(lattitude,6) + ";" + String(longitude,6);
      sendMessage(msg);
      orders = false;
    }
  } 
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
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