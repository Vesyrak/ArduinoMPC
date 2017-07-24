#include <MPC.h>
#include <LCDControl.h>

#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   0
#define btnSELECT 4
#define btnNONE   5
#define btnMETA   6


MPC client;
int history=0;
int current=0;
int timer=0;

void setup(){
  client.begin();
}
void loop(){
  current=getInput();
  if(current==history)
    current=btnNONE;
  else history=current;
  if(current!=btnNONE)
    client.sendCommand(current);
  client.read();
  delay(200);
}

int getInput(){
  int adc_key_in = analogRead(0);     
 if (adc_key_in < 850 && adc_key_in > 600) {
  timer++;
  if(timer==5){
    timer=0;
    return btnMETA;
  }
 }
 else if(timer==1){
  timer=0;
  return btnSELECT;
 }
 
 if (adc_key_in > 1000) return btnNONE; 
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 150)  return btnUP; 
 if (adc_key_in < 300)  return btnDOWN; 
 if (adc_key_in < 600)  return btnLEFT; 
 return btnNONE;
}



