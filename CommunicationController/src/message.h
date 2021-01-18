#include <Arduino.h>
#ifndef Message_h
#define Message_h

class Message
{
  public:
    Message();
    void SETUP();
    void syncTime();
    void printFirmwareRevision();
    String intToHex(int myInt);
    String floatToHex(float myFloat);
    String stringToHex(String myString);
    char* string2char(String command);
    void SERCOM1_Handler();
    void sendMessage(String msg);
    void getMessage();
    void getGPSData();
    void getSignal();
    float lattitude, longitude; 
    int signalQuality = -1;
    int err;
    bool orders = false;
};

extern Message msg;

#endif