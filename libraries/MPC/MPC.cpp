#include "MPC.h"
LCDControl screen(8,9,4,5,6,7, 16, 2);
MPC::MPC(){
}
void MPC::begin(){
    Serial.begin(9600);
}
void MPC::sendCommand(int i){
    Serial.write(i);
}

void MPC::sendString(String command){
    Serial.print(command);
}

void MPC::read(){
    while(Serial.available()){
        char c=Serial.read();
        if (c=='\n')
        {
            parseMessage();
            message="";
        }
        else message+=c;
    }
    screen.update();
}

void MPC::parseMessage(){
    type=message[0];
    message=message.substring(1, message.length());
    switch(type){
        case 'N':
            printName();
            break;
        case 'T':
            printTitle();
            break;
        case 'X':
            printMeta1();
            break;
        case 'Y':
            printMeta2();
            break;

    }
}

void MPC::printName(){
    if(message.length()<16){
        screen.setCursor(0,0, true);
        screen.print(&message);
    }
    else{
        screen.scrollText(&message, 5,0);
    }
}
void MPC::printTitle(){
    if(message.length()<16){
        screen.setCursor(0,1, true);
        screen.print(&message);
    }
    else{
        screen.scrollText(&message, 5,1);
    }
}

void MPC::printMeta1(){
    screen.setCursor(0,0,true);
    screen.print(&message);
}
void MPC::printMeta2(){
    screen.setCursor(0,1,true);
    screen.print(&message);
}
