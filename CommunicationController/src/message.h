#include <Arduino.h>
#ifndef Message_h
#define Message_h

class Message
{
  public:
    Message();
    void SETUP();
    void printFirmwareRevision();
    void sendMessage(uint8_t* msg, size_t size);
    void sendGpsMessage(float lattitude, float longitude, int day, int month, int hour, int minute);
    void getMessage();
    void getSignal();
    int signalQuality = -1;
    int err;
    bool orders = false;
};

extern Message msg;

#endif