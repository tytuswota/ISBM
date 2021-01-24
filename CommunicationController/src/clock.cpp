// Includes
#include <Arduino.h>
#include <clock.h>
#include <RTCZero.h>

// RTC libarary that uses the RTC from sparkfun controller
RTCZero rtc;

// Clock class
Clock::Clock()
{

}

// Begin the RTC
void Clock::SETUP(int alarmMinutes)
{
    rtc.begin();
}

// Sync the time from the RTC
void Clock::syncTime(int hour, int minute, int second, int day, int month, int year)
{
    // Set the time layout
    rtc.setTime(hour, minute, second);

    // RTC library expects years from 2000
    rtc.setDate(day, month, (year - 2000)); // 2021 is 21 years: 2021 - 2000 = 21
}

// Sets the alarm in minutes
void Clock::setAlarmTime(int alarmMinutes)
{
    rtc.setAlarmMinutes(alarmMinutes);
}

// Debug function
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

// Get the data from the RTC
void Clock::getDateTime(int &day, int &month, int &hour, int &minute)
{
    month = rtc.getMonth();
    day = rtc.getDay();
    hour = rtc.getHours();
    minute = rtc.getMinutes();
}

// Check if the alarm time has been reached
bool Clock::alarmHasMatch(int hour, int minute)
{
    if(hour == rtc.getHours() && minute == rtc.getMinutes()) 
    {
        return true;
    }
    else
    {
        return false;
    }
}