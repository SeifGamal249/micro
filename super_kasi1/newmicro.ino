#include <Servo.h>

int ser_pin=8;
int ser_motion=0;
int sw_1=0;
//int sw_1_pin=
int sw_2=0;
//int sw_2_pin=
int sw_3=0;
//int sw_3_pin=
int sw_4=0;
//int sw_4_pin=


Servo servomove;

void setup(){
  Serial.begin(9600);
  pinMode(ser_pin,OUTPUT);
  pinMode(sw_1_pin,INPUT);
  pinMode(sw_2_pin,INPUT);
  pinMode(sw_3_pin,INPUT);
  pinMode(sw_4_pin,INPUT);

  servomove.attach(ser_pin);
  servomove.write(0);

  delay(50);
}
void loop(){

  sw_1.digitalRead(sw_1_pin);
  sw_2.digitalRead(sw_2_pin);
  sw_3.digitalRead(sw_3_pin);
  sw_4.digitalRead(sw_4_pin);
  
  if(sw_1==HIGH)
  {
    //L=L1;
    for(ser_motion=0;ser_motion<=(theta1);ser_motion++)        //theta1 angle for L1
    {
      servomove.write(ser_motion);
      delay(2);
    }
   
  }
  else if(sw_2==HIGH)
  {
    //L=L2;
    for(ser_motion=0;ser_motion<=(theta2);ser_motion++)        //theta2 angle for L2
    {
      servomove.write(ser_motion);
      delay(2);
    }
   
  }  
  else if(sw_3==HIGH)
  {
    //L=L3;
    for(ser_motion=0;ser_motion<=(theta3);ser_motion++)        //theta3 angle for L3
    {
      servomove.write(ser_motion);
      delay(2);
    }
   
  }
  else if(sw_4==HIGH)
  {
    //L=L4;
    for(ser_motion=0;ser_motion<=(theta4);ser_motion++)        //theta4 angle for L4
    {
      servomove.write(ser_motion);
      delay(2);
    }
   
  }
    
  
}
