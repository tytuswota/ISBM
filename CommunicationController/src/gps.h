// Includes
#include <Arduino.h>
#ifndef GPS_h
#define GPS_h

// GPS class
class GPS
{
  public:
    GPS();
    void SETUP();
    void getDateTime(byte &date, byte &time);
    void getLattitudeLongitude(Uart &gpsSerial, float &lattitude, float &longitude, int &day, int &month, int &hour, int &minute);
    void sercom1Handler();
    void syncTime(int &day, int &month, int &hour, int minute);
};  

extern GPS gps;

#endif