// Converted from Flowcode C to Arduino IDE
// Target: Arduino with ATmega328P microcontroller
#include <Servo.h>
#include <Keypad.h>
//#include "HX711.h"


// Global Variables
Servo myServo;
//HX711 scale;

int servoPin = 44; // Servo connected to pin 9

int buttonGroundFloor = 2; // Ground Floor Button
int buttonFirstFloor = 3;  // First Floor Button
int buttonSecondFloor = 4; // Second Floor Button
const byte ROWS = 1; // Number of rows on the keypad
const byte COLS = 3; // Number of columns on the keypad
//motor 1 inputs
const int motorPin1 = 41;//52 // Motor control pin 1 (to L293D Input 1)
const int motorPin2 = 39; //50 // Motor control pin 2 (to L293D Input 2)
//motor 2 inputs
const int motorPin3 = 9;
const int motorPin4 = 10;
//motor 3 inputs
const int motorPin5 = 50;//52
const int motorPin6 = 52;//50
//FOR FLOOR 1
const int limitSwitch_1 = 6; // Start switch connected to pin 2
const int limitSwitch_2 = 47;  // Stop switch connected to pin 3
//FOR FLOOR 2
const int limitSwitch_3 = 51; // Start switch connected to pin 2
const int limitSwitch_4 = 53;  // Stop switch connected to pin 3
//FOR FLOOR 3
const int limitSwitch_5 = 45; // Start switch connected to pin 2
const int limitSwitch_6 = 43;  // Stop switch connected to pin 3

bool motorRunning = true;
float floor_0=0;
// Pin definitions
//const int LOADCELL_DOUT_PIN = 40; // Data pin (DT)
//const int LOADCELL_SCK_PIN = 38;  // Clock pin (SCK)

// Initialize HX711


char keys[ROWS][COLS] = {
  {'1', '2', '3'}
};
byte rowPins[ROWS] = {8}; // Connect rows to these Arduino pins
byte colPins[COLS] = {11, 12, 13}; // Connect columns to these Arduino pins

int currentState = 1; // Elevator starts at Ground Floor
int servoPosition = 90; // Servo's default position (neutral)
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  // Initialize Servo
  myServo.attach(servoPin);
  myServo.write(servoPosition);

  // Initialize Buttons
  pinMode(buttonGroundFloor, INPUT_PULLUP);
  pinMode(buttonFirstFloor, INPUT_PULLUP);
  pinMode(buttonSecondFloor, INPUT_PULLUP);
    // Set motor pins as output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
   // motor pins as output
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);   
     // motor pins as output
  pinMode(motorPin5, OUTPUT);
  pinMode(motorPin6, OUTPUT);  


  // Set switch pins as input with pull-up resistors
  pinMode(limitSwitch_1, INPUT);
  pinMode(limitSwitch_2, INPUT);
    // Set switch pins as input with pull-up resistors
  pinMode(limitSwitch_3, INPUT);
  pinMode(limitSwitch_4, INPUT);
    // Set switch pins as input with pull-up resistors
  pinMode(limitSwitch_5, INPUT);
  pinMode(limitSwitch_6, INPUT);
  
  /*
  Serial.println("HX711 Weight Measurement");

  // Initialize the scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Calibration factor (adjust based on your calibration)
  scale.set_scale(2280.f); // Set the calibration factor
  scale.tare();            // Reset the scale to 0
  */

  // Initialize Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Read Button States
  bool groundFloorPressed = digitalRead(buttonGroundFloor);
  bool firstFloorPressed = digitalRead(buttonFirstFloor);
  bool secondFloorPressed = digitalRead(buttonSecondFloor);
  char key = keypad.getKey();
  //loadcell();


  // Elevator Logic
  switch (currentState) {
    case 1: // Ground Floor
      if (groundFloorPressed || key == '1') {
        Serial.println("Ground Floor Button Pressed. Holding Position.");
        //myServo.write(90); // Stay in position
        startMotor_1();
          // Check if the start switch is pressed
        

      }
      else if (firstFloorPressed || key == '2') {
        floor_0=1;
        Serial.println("Moving to First Floor.");
        startrevMotor_1();
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.01);
        }
        startMotor_2();

        //moveServo(100); // Move to First Floor position
        //moveServo(120); // Move to First Floor position
        //moveServo(100); // Move to First Floor position

        //delay(2000); // Wait for 2 seconds
        moveServo(90); // Return to neutral
        currentState = 2;
      }
      else if (secondFloorPressed || key == '3') {
        floor_0=2;
        Serial.println("Moving to Second Floor.");
        startrevMotor_2();
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.02);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.02);
        }
        startMotor_3();
        //moveServo(100); // Move to Second Floor position
        //moveServo(120); // Move to Second Floor position
        //moveServo(100); // Move to Second Floor position

        //delay(4000); // Wait for 4 seconds
        moveServo(90); // Return to neutral
        currentState = 3;
      }
      break;

    case 2: // First Floor
      if (firstFloorPressed || key == '2') {
        Serial.println("First Floor Button Pressed. Holding Position.");
        //myServo.write(90); // Stay in position
        startMotor_2();
      }
      else if (groundFloorPressed || key == '1') {
        floor_0=1;
        Serial.println("Returning to Ground Floor.");
        startrevMotor_2();
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=20;i>90;i++){
          moveServo(i);
          //delay(0.01);
        }
        startMotor_1();
        //moveServo(80);
        //moveServo(60);
        //moveServo(80);

        //delay(2000); // Wait for 2 seconds
        moveServo(90); // Return to neutral
        currentState = 1;
      }
      else if (secondFloorPressed || key == '3') {
        floor_0=1;
        Serial.println("Moving to Second Floor.");
        startrevMotor_2();
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.01);
        }
        startMotor_3();
        //moveServo(100); // Move to Second Floor position
        //moveServo(120); // Move to Second Floor position
        //moveServo(100); // Move to Second Floor position
        //delay(2000); // Wait for 2 seconds
        moveServo(90); // Return to neutral
        currentState = 3;
      }
      break;

    case 3: // Second Floor
      if (secondFloorPressed || key == '3') {
        Serial.println("Second Floor Button Pressed. Holding Position.");
        //myServo.write(90); // Stay in position
        startMotor_3();
      }
      else if (groundFloorPressed || key == '1') {
        floor_0=1;
        Serial.println("Returning to Ground Floor.");
        startrevMotor_3();
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.02);
        }
        for(int i=20;i<90;i++){
          moveServo(i);
          //delay(0.02);
        }
        startMotor_1();
        //moveServo(80);
        //moveServo(60);
        //moveServo(80);
        //delay(4000); // Wait for 4 seconds
        moveServo(90); // Return to neutral
        currentState = 1;
      }
      else if (firstFloorPressed || key == '2') {
        floor_0=0.5;
        Serial.println("Returning to First Floor.");
        startrevMotor_3();
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=20;i<90;i++){
          moveServo(i);
          //delay(0.01);
        }
        startMotor_2();
        //moveServo(80);
        //moveServo(60);
        //moveServo(80);
        //delay(2000); // Wait for 2 seconds
        moveServo(90); // Return to neutral
        currentState = 2;
      }
      break;

    default:
      Serial.println("Error: Unknown State.");
      currentState = 1; // Reset to Ground Floor
      break;
  }
}

// Helper Function to Move Servo
void moveServo(int position) {
  myServo.write(position);
  delay(70*floor_0);
  myServo.write(90);
}

void startMotor_1() {
  // Rotate motor in one direction
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  while (digitalRead(limitSwitch_1) == HIGH) {
    // Wait until the limit switch is triggered
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_1();

  Serial.println("Motor stopped by limit switch.");
}

void startrevMotor_1(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,HIGH);
  while (digitalRead(limitSwitch_2) == HIGH) {
    // Wait until the limit switch is triggered
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_1();

  Serial.println("Motor stopped by limit switch.");
}

void stopMotor_1() {
  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
void startMotor_2() {
  // Rotate motor in one direction
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.println(digitalRead(limitSwitch_3));
  while (digitalRead(limitSwitch_3) == HIGH) {
    Serial.println("Door open");
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_2();

  Serial.println("Motor stopped by limit switch.");
}

void startrevMotor_2(){
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4,HIGH);
  while (digitalRead(limitSwitch_4) == HIGH) {
   Serial.println("Door Close");
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_2();

  Serial.println("Motor stopped by limit switch.");
}

void stopMotor_2() {
  // Stop the motor
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
void startMotor_3() {
  // Rotate motor in one direction
  digitalWrite(motorPin5, HIGH);
  digitalWrite(motorPin6, LOW);
  while (digitalRead(limitSwitch_5) == HIGH) {
     Serial.println("Door open");
    // Wait until the limit switch is triggered
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_3();

  Serial.println("Motor stopped by limit switch.");
}
 //reversing the move of the motor
void startrevMotor_3(){
  digitalWrite(motorPin5, LOW);
  digitalWrite(motorPin6,HIGH);
  while (digitalRead(limitSwitch_6) == HIGH) {
    // Wait until the limit switch is triggered
  }

  // Once the limit switch is triggered, stop the motor
  stopMotor_3();

  Serial.println("Motor stopped by limit switch.");
}

void stopMotor_3() {
  // Stop the motor
  digitalWrite(motorPin5, LOW);
  digitalWrite(motorPin6, LOW);
}

// load cell code
/*void loadcell(){
  if (scale.is_ready()) {
    // Read the weight in grams
    float weight = scale.get_units(10); // Average of 10 readings
    Serial.print("Weight: ");
    Serial.print(weight, 2); // Print with two decimal places
    Serial.println(" g");
    while(weight>450){
      weight = scale.get_units(10);
      Serial.print("over weight");

    }
    Serial.print("weight is okey");

  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000); // Wait for 1 second before next reading
}*/
