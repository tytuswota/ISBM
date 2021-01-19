#include <Arduino.h>
#include <gps.h>
#include <TinyGPS++.h>
#include <clock.h>

TinyGPSPlus gpsModule;

void GPS::SETUP()
{
    clock.SETUP(40);
}

void GPS::getLattitudeLongitude(Uart &gpsSerial1, float &lattitude, float &longitude, int &x)
{
    //TO DO attempt timeout 
    while(1)
    {
        while(gpsSerial1.available() > 0)
        {
            gpsModule.encode(gpsSerial1.read());
        }

        if(gpsModule.location.isUpdated() && gpsModule.date.isUpdated() && gpsModule.time.isUpdated())
        {
            lattitude = gpsModule.location.lat();
            longitude = gpsModule.location.lng();
            //+1 hour for CET
            clock.syncTime((gpsModule.time.hour() + 1), gpsModule.time.minute(), 
            gpsModule.time.second(), gpsModule.date.day(), gpsModule.date.month(), gpsModule.date.year());
            
            break;
        }
    }
}

void GPS::getDateTime(byte &date, byte &time)
{

}


