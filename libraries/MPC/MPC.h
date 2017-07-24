#ifndef MPC_h
#define MPC_h
#include "Arduino.h"
#include "LCDControl.h"
class MPC{
    public:
        MPC();
        void begin();
        void sendCommand(int i);
        void read();
    private:
        void sendString(String command);
        String message;
        char type;
        void printName();
        void printTitle();
        void parseMessage();
        void printMeta1();
        void printMeta2();

};
#endif
