#include <Servo.h>

int ser_pin=8;
int ser_motion=0;
int sw_1_pin=2;
int sw_2_pin=3;
int sw_3_pin=4;
int desired=0;
int current=0;
int i=0;
int sw[3]={sw_1_pin,sw_2_pin,sw_3_pin};
int moveagain=0;
bool again=true;
bool again_1=true;
bool again_2=true;

Servo servomove;

void setup(){
  Serial.begin(9600);
  pinMode(ser_pin,OUTPUT);
  pinMode(sw_1_pin,INPUT);
  pinMode(sw_2_pin,INPUT);
  pinMode(sw_3_pin,INPUT);
  servomove.attach(ser_pin);
  delay(50);
}
void loop(){
  
          if(digitalRead(sw[0])==HIGH&&again==true)
           {
             
             desired=10; // angle according to length
             moveagain=1;
             again=false;
           }
                     
          else if(digitalRead(sw[1])==HIGH&&again_1==true)
           {
             
             desired=10*2-desired; // angle according to length
             moveagain=1;
             again_1=false;
           }
                     
          else if(digitalRead(sw[2])==HIGH&&again_2==true)
           {
             
             desired=10*3-desired; // angle according to length
             moveagain=1;
             again_2=false;
           }
   
           else
            {
             desired=0;
    
            }
  
  
  if ( (moveagain==1) &&(desired>current))
  {
    for(ser_motion=0;ser_motion<=desired;ser_motion++)//theta1 angle for L1 the target angle
    {
      servomove.write(90);//speed of the servo
      delay(50);//time to reach the required door
    }
  }
  else if (desired==current)
  {
    //servomove.detach();// to fully stop the servo
    servomove.write(93);//the angle of stop of the servo
  }
}