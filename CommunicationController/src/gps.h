#include <Arduino.h>
#ifndef GPS_h
#define GPS_h

class GPS
{
  public:
    GPS();
    void SETUP();
    void getDateTime(byte &date, byte &time);
    void getLattitudeLongitude(Uart &gpsSerial, float &lattitude, float &longitude, int &day, int &month, int &hour, int minute);
    void SERCOM1_Handler();
    void syncTime(int &day, int &month, int &hour, int minute);
};  

extern GPS gps;

#endif