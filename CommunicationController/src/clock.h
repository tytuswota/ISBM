#include <Arduino.h>
#ifndef Clock_h
#define Clock_h

class Clock
{
  public:
    Clock();
    void SETUP(int alarmMinutes);
    byte hour, minute, second, day, month, year;
    void syncTime(byte hour, byte minute, byte second, byte day, byte month, byte year);
    bool alarmTrigered = false;
    void setAlarmTime(int alarmMinutes);
    int alarmMinute;
};  

extern Clock clock;

#endif