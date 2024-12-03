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
  for(i=0;i<3;i++) 
  {
     if(digitalRead(sw[i])==HIGH)
     { 
        for(i=0;i<3;i++)
        {     
           if(digitalRead(sw[i])==HIGH)
           {
             
             desired=current+10; // angle according to length
             moveagain=1;
           }

        }
     }    
    else
    {
       desired=0;
    
     }
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
    //servomove.write();
    //servomove.detach();
    //moveagain=0;
    servomove.write(93);

  }

}

