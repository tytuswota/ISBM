#include <Arduino.h>
#include <clock.h>
#include <RTCZero.h>

RTCZero rtc;

void Clock::SETUP(int alarmMinutes)
{
    rtc.begin();
}

void Clock::syncTime(byte hour, byte minute, byte second, byte day, byte month, byte year)
{
    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month, year);
}

void Clock::setAlarmTime(int alarmMinutes)
{
    rtc.setAlarmMinutes(alarmMinutes);
}