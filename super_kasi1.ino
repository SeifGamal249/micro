#include <Keypad.h>
#include <Servo.h>

int ser_pin=8;
int ser_motion=0;
int rows=1;
int columns=3;
int rows_pins[rows]=2;
int columns_pins[columns]={-3,4,-5};
char key_servo[rows][columns]={'1','2','3'};


Servo servomove;
Keypad keypad = Keypad( makeKeymap(key_servo), rows_pins, columns_pins, rows, columns );


void setup(){
  Serial.begin(9600);
  char key_input = keypad.getKey(keypad);
  pinMode(rows_pins,INPUT);
  pinMode(columns_pins,INPUT);
  pinMode(ser_pin,OUTPUT);
  servomove.attach(ser_pin);
  servomove.write(0);
  delay(50);
}
void loop(){
  if(key_input=='1'){
    
    for(ser_motion=0;ser_motion<=60;ser_motion++)
    {
      
      servomove.write(ser_motion);
      delay(50);
    }
  }
  if(key_input=='2'){
        for(ser_motion;ser_motion<=120;ser_motion++)
        {
      
          servomove.write(ser_motion);
          delay(50);
        }
  }
  if(key_input=='3'){
        for(ser_motion;ser_motion<=180;ser_motion++)
        {
      
          servomove.write(ser_motion);
          delay(50);
        }
  }
}


