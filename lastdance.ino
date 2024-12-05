#include <Servo.h>

int ser_pin=8;
int ser_motion=0;
int sw_1_pin=2;
int sw_2_pin=3;
int sw_3_pin=4;
int sw_stop_pin=5;
int desired=0;
int current=0;
int i=0;
int sw[4]={sw_1_pin,sw_2_pin,sw_3_pin,sw_stop_pin};
bool again=true;
bool again_1=true;
bool again_2=true;
int floor_current=0;

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
	again=false;
	floor_current=1;
  Serial.println("GROUND");
  
}            
else if(digitalRead(sw[1])==HIGH&&again_1==true)
{
  
	desired=10; // angle according to length
	again_1=false;
	floor_current=2;
  Serial.println("FIRST");
}                  
else if(digitalRead(sw[2])==HIGH&&again_2==true)
{            
	desired=10*2-desired; // angle according to length
	again_2=false;
	floor_current=3;
  Serial.println("SECOND");

}
else if(digitalRead(sw[3])==HIGH)
{
  Serial.println("STOP");
	servomove.detach();// to fully stop the servo
}
else 
{
	desired=0;
}
if ((desired>current))
{
      servomove.write(88);//speed of the servo
      delay(desired*50);
      servomove.write(90);//speed of the servo
      delay(desired*50);
      servomove.write(92);//speed of the servo
      delay(desired*50);
      servomove.write(93);//speed of the servo
    
}
else if (desired==current)
{
    servomove.write(93);//the angle of stop of the servo
}
for (int j=0;j<3;j++)
{
    if((digitalRead(sw[j])==HIGH)&&(floor_current>(j+1)))
    {
      floor_current=j+1;
      desired=10*floor_current-10*j;
      again=true;
      again_1=true;
      again_2=true;
        servomove.write(98);
        delay(desired*50);
        servomove.write(100);
        delay(desired*50);
        servomove.write(98);
        delay(desired*50);
        servomove.write(93);
    }
    if(digitalRead(sw[0])==HIGH){Serial.println("GROUND");}
    if(digitalRead(sw[1])==HIGH){Serial.println("FIRST");}
    if(digitalRead(sw[2])==HIGH){Serial.println("SECOND");}
  }
}
