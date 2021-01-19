#include <Arduino.h>
#ifndef GPS_h
#define GPS_h

class GPS
{
  public:
    GPS();
    void SETUP();
    void getDateTime(byte &date, byte &time);
    void getLattitudeLongitude(Uart &gpsSerial, float &lattitude, float &longitude, int &x);
    void SERCOM1_Handler();
};  

extern GPS gps;

#endif