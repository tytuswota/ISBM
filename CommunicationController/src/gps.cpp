// Includes
#include <Arduino.h>
#include <gps.h>
#include <TinyGPS++.h>
#include <clock.h>

TinyGPSPlus gpsModule;

// Setup clock
void GPS::SETUP()
{
    clock.SETUP(40);
}

// Get the GPS module data
void GPS::getTime()
{
    clock.syncTime((gpsModule.time.hour() + 1), gpsModule.time.minute(), // +1 hour for CET
    gpsModule.time.second(), gpsModule.date.day(), gpsModule.date.month(), gpsModule.date.year());
}

// Gets the data fromthe GPS module and the RTC
void GPS::getLattitudeLongitude(Uart &gpsSerial1, float &lattitude, float &longitude, int &day, int &month, int &hour, int &minute)
{ 
    while(1)
    {
        // Check if the serial for GPS is available
        while(gpsSerial1.available() > 0)
        {
            // Read from the serial
            gpsModule.encode(gpsSerial1.read());
        }

        // Check if the location, date and time is updated
        if(gpsModule.location.isUpdated() && gpsModule.date.isUpdated() && gpsModule.time.isUpdated())
        {
            // Update the values
            lattitude = gpsModule.location.lat();
            longitude = gpsModule.location.lng();
            day = gpsModule.date.day();
            month = gpsModule.date.month();
            hour = gpsModule.time.hour();
            minute = gpsModule.time.minute();

            // Get the GPS module data
            getTime();

            break;
        }
    }
}

// Sync the time with the RTC
void GPS::syncTime(int &day, int &month, int &hour, int minute)
{
    day = gpsModule.date.day();
    month = gpsModule.date.month();
    hour = gpsModule.time.hour();
    minute = gpsModule.time.minute();

    // Get the GPS module data
    getTime();
}