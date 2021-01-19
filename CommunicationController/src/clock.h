#include <Arduino.h>
#ifndef Clock_h
#define Clock_h

class Clock
{
  public:
    Clock();
    void SETUP(int alarmMinutes);
    byte hour, minute, second, day, month, year;
    void syncTime(int hour, int minute, int second, int day, int month, int year);
    bool alarmTrigered = false;
    void setAlarmTime(int alarmMinutes);
    int alarmMinute;
    void showDateTime();
};  

extern Clock clock;

#endif