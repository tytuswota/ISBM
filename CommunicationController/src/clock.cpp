#include <Arduino.h>
#include <clock.h>
#include <RTCZero.h>

RTCZero rtc;

Clock::Clock()
{

}

void Clock::SETUP(int alarmMinutes)
{
    rtc.begin();
}

void Clock::syncTime(int hour, int minute, int second, int day, int month, int year)
{
    rtc.setTime(hour, minute, second);
    //rtc library expects years from 2000
    rtc.setDate(day, month, (year - 2000));
}

void Clock::setAlarmTime(int alarmMinutes)
{
    rtc.setAlarmMinutes(alarmMinutes);
}

void Clock::showDateTime()
{
    SerialUSB.print(rtc.getDay());
    SerialUSB.print("/");
    SerialUSB.print(rtc.getMonth());
    SerialUSB.print("/");
    SerialUSB.println(rtc.getYear());

    SerialUSB.print(rtc.getHours());
    SerialUSB.print(":");
    SerialUSB.print(rtc.getMinutes());
    SerialUSB.print(":");
    SerialUSB.println(rtc.getSeconds());
}

void Clock::getDateTime(int &day, int &month, int &hour, int &minute)
{
    month = rtc.getMonth();
    day = rtc.getDay();
    hour = rtc.getHours();
    minute = rtc.getMinutes();
}

bool alarmHasMatch(int hour, int minute)
{
    if(hour == rtc.getHours() && minute == rtc.getMinutes()) return true;
    return false;
}