#include <LiquidCrystal.h>
#include "Arduino.h"
#include "LCDControl.h"

LCDControl::LCDControl(int RS, int E, int d4, int d5, int d6, int d7, int width, int length):lcd(RS, E, d4,d5,d6,d7)
{
    screenWidth=width;
    screenLength=length;
    buffer = (uint8_t**)calloc(length, sizeof(uint8_t *));
    for(int i=0; i<width; i++){
        buffer[i]=(uint8_t*)calloc(width, sizeof(uint8_t));
    }
    for(int i=0; i<length; i++){
        for(int j=0; j<width; j++){
            buffer[i][j]=0;
        }
    }
    lcd.begin(width, length);
}

void LCDControl::setCursor(int x, int y, bool free){
    cursorPosX=x;
    cursorPosY=y;
    if(free)
    {
        for(int i=0;i<screenWidth;i++){
            buffer[y][i]=0;
        }
        if(((round(pow(2,cursorPosY)))&bufferLines)){
            bufferLines-=round(pow(2,cursorPosY));
        }
    }
}

void LCDControl::print(String* string){
    changed=true;
    int i=0;
    while(cursorPosX<screenWidth&&i<string->length()){
        buffer[cursorPosY][cursorPosX]=(uint8_t)string->charAt(i);
        i++;
        cursorPosX++;
    }
}

void LCDControl::update(){
    updateScrollText();
    if(changed){
        changed=false;
        lcd.clear();
        for(int i=0; i<screenLength; i++)
            for (int j=0; j<screenWidth; j++)
            {
                if(buffer[i][j]!=0)
                {
                    lcd.setCursor(j,i);
                    lcd.write(buffer[i][j]);
                }
            }
    }
}

inline void LCDControl::write(uint8_t character){
    changed=true;
    if(cursorPosX<screenWidth)
    {
        buffer[cursorPosX][cursorPosY]=character;
        cursorPosX++;
    }
}



int LCDControl::centerText(String* message){
    return (screenWidth-message->length())/2;
}

void LCDControl::updateScrollText(){
    for(int mask=0; mask<8; mask++){
        if(round(pow(2,mask))&bufferLines){
            if(tickCounters[mask]==5){
                tickCounters[mask]=0;
                setCursor(0,mask);
                String s=stringBuffer[mask].substring(countBuffer[mask],stringBuffer[mask].length());
                print(&s);
                if(s.length()>screenWidth){
                    countBuffer[mask]++;
                }
                else {
                    countBuffer[mask] =0;
                    tickCounters[mask]=-5;
                }
            }
            else tickCounters[mask]++;
        }
    }
}

void LCDControl::scrollText(String* message, int delayTicks, int line){
    if(!((round(pow(2,line)))&bufferLines))
        bufferLines+=pow(2,line);

    if(stringBuffer[line]!=*message)
    {
        stringBuffer[line]=*message;
        countBuffer[line]=0;
        tickCounters[line]=0;
    }
}

void LCDControl::printBuffer(){
    for(int i=0; i<screenLength; i++)
    {
        for (int j=0; j<screenWidth; j++)
        {
            Serial.print(buffer[i][j]);
            Serial.print(", ");
        }
        Serial.println();
    }
    Serial.println("------");
}
