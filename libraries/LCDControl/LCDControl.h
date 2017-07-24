#ifndef LCDControl_h
#define LCDControl_h
#include "Arduino.h"
#include <LiquidCrystal.h>
class LCDControl{
    public:
        LiquidCrystal lcd;
        LCDControl(int RS, int E, int d4, int d5, int d6, int d7, int width, int length);
        void setCursor(int x, int y, bool free=false);
        void print(String* string);
        void write(uint8_t character);
        void updateScrollText();
        void scrollText(String* message, int delayTicks, int line);
        void update();
    private:
        void printBuffer();
        int screenWidth;
        int screenLength;
        int cursorPosX=0;
        int cursorPosY=0;
        uint8_t **buffer;
        int bufferLines=0;
        String stringBuffer[8];
        int countBuffer[8];
        int tickCounters[8];
        bool changed=false;
        int centerText(String* message);
};
#endif
