#include <LiquidCrystal.h> //Libraries
#include <EEPROM.h>
#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define bt_up     A0
#define bt_down   A1
#define bt_reset  A2
#define bt_go     A3
#define buzzer 9

long d1=0, d2=0, d3=0;
int flag1=0, flag2=0, timer=0;

void setup(){ // put your setup code here, to run once
myStepper.setSpeed(60);
Serial.begin(9600);
 pinMode(bt_up,    INPUT_PULLUP);
 pinMode(bt_down,  INPUT_PULLUP);
 pinMode(bt_reset, INPUT_PULLUP);
 pinMode(bt_go, INPUT_PULLUP);
 pinMode(buzzer, OUTPUT);

  
 lcd.begin(16, 2);
 lcd.clear();
 lcd.setCursor (0,0);
 lcd.print("   MT RAININ   ");
 lcd.setCursor (0,1);
 lcd.print("  Test Fixture  ");
 delay(2500);
 lcd.clear();

if(EEPROM.read(50)==0){
}
else{WriteEeprom();}
EEPROM.write(50,0); 
ReadEeprom();
}

void loop(){  
if(digitalRead (bt_up) == 0){ 
if(flag1==0){ flag1=1;
d1=d1+1;
if(d1>9){d1=0; d2=d2+1;}  
if(d2>9){d2=0; d3=d3+1;} 
if(d3>9){d3=0;}
WriteEeprom(); 
}
}
else{flag1=0;}

if(digitalRead (bt_down) == 0){ 
if(flag2==0){ flag2=1;
d1=d1-1;
if(d1<0){d1=9; d2=d2-1;}  
if(d2<0){d2=9; d3=d3-1;} 
if(d3<0){d3=9;} 
WriteEeprom(); 
}  
}
else{flag2=0;}

if(digitalRead (bt_reset) == 0){ 
digitalWrite(buzzer, HIGH);
if(timer<7){timer=timer+1;}
if(timer==7){
d1=0, d2=0, d3=0;
WriteEeprom();
}   
}
else{digitalWrite(buzzer, LOW); timer=0;}

lcd.setCursor (1,0);
lcd.print("TURN   COUNTER");
lcd.setCursor(5,1);
lcd.print(d3);
lcd.print(d2);
lcd.print(d1);

delay(10);

if(digitalRead (bt_go) == 0)
{
int turn_count = 100*d3 + 10*d2 + d1;  
  // put your main code here, to run repeatedly:
for (int i=0; i<turn_count; i++) // declares i, tests if less 
{ // than 20, increments i by 1
  myStepper.step(stepsPerRevolution);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
  delay(200);
}
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(1000);
}
}


void ReadEeprom() {
d1=EEPROM.read(1);
d2=EEPROM.read(2);
d3=EEPROM.read(3);
}

void WriteEeprom() {  
EEPROM.write(1, d1);
EEPROM.write(2, d2);
EEPROM.write(3, d3);
}
