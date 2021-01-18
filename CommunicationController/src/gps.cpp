#include <Arduino.h>
#include <gps.h>
#include <TinyGPS++.h>

TinyGPSPlus gpsModule;
Uart gpsSerial(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);

void GPS::SETUP()
{
    gpsSerial.begin(9600);
}

void GPS::getDateTime(byte &date, byte &time)
{

}

void GPS::getLattitudeLongitude(float &lattitude, float &longitude)
{
    while(1)
    {
        while(gpsSerial.available() > 0)
        {
            gpsModule.encode(gpsSerial.read());
        }

        if(gpsModule.location.isUpdated())
        {
            lattitude = gpsModule.location.lat();
            longitude = gpsModule.location.lng();
            break;
        }
    }

    SerialUSB.println("lat: " + String(lattitude, 6));
    SerialUSB.println("long: " + String(longitude, 6));
}

void GPS::SERCOM1_Handler()
{
  gpsSerial.IrqHandler();
}
