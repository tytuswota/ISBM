#include <Arduino.h>
#include <clock.h>
#include <RTCZero.h>

RTCZero rtc;

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
    SerialUSB.println(rtc.getDay());
    SerialUSB.println(rtc.getMonth());
    SerialUSB.println(rtc.getYear());

    SerialUSB.println(rtc.getHours());
    SerialUSB.println(rtc.getMinutes());
    SerialUSB.println(rtc.getSeconds());
}