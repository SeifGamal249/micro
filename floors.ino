// Converted from Flowcode C to Arduino IDE
// Target: Arduino with ATmega328P microcontroller
#include <Servo.h>
#include <Keypad.h>

// Global Variables
Servo myServo;

int servoPin = 7; // Servo connected to pin 9

int buttonGroundFloor = 2; // Ground Floor Button
int buttonFirstFloor = 3;  // First Floor Button
int buttonSecondFloor = 4; // Second Floor Button
const byte ROWS = 1; // Number of rows on the keypad
const byte COLS = 3; // Number of columns on the keypad
int floor_0=0;

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

  // Initialize Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Read Button States
  bool groundFloorPressed = digitalRead(buttonGroundFloor);
  bool firstFloorPressed = digitalRead(buttonFirstFloor);
  bool secondFloorPressed = digitalRead(buttonSecondFloor);
  char key = keypad.getKey();


  // Elevator Logic
  switch (currentState) {
    case 1: // Ground Floor
      if (groundFloorPressed || key == '1') {
        Serial.println("Ground Floor Button Pressed. Holding Position.");
        //myServo.write(90); // Stay in position
      }
      else if (firstFloorPressed || key == '2') {
        floor_0=1;
        Serial.println("Moving to First Floor.");
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.01);
        }

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
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.02);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.02);
        }
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
      }
      else if (groundFloorPressed || key == '1') {
        floor_0=1;
        Serial.println("Returning to Ground Floor.");
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=20;i>90;i++){
          moveServo(i);
          //delay(0.01);
        }
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
        for(int i=90;i<150;i++){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=150;i>90;i--){
          moveServo(i);
          //delay(0.01);
        }
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
      }
      else if (groundFloorPressed || key == '1') {
        floor_0=2;
        Serial.println("Returning to Ground Floor.");
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.02);
        }
        for(int i=20;i<90;i++){
          moveServo(i);
          //delay(0.02);
        }
        //moveServo(80);
        //moveServo(60);
        //moveServo(80);
        //delay(4000); // Wait for 4 seconds
        moveServo(90); // Return to neutral
        currentState = 1;
      }
      else if (firstFloorPressed || key == '2') {
        floor_0=1;
        Serial.println("Returning to First Floor.");
        for(int i=90;i>20;i--){
          moveServo(i);
          //delay(0.01);
        }
        for(int i=20;i<90;i++){
          moveServo(i);
          //delay(0.01);
        }
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