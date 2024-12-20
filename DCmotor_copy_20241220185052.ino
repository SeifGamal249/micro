// Pin definitions
const int motorPin1 = 9; // Motor control pin 1 (to L293D Input 1)
const int motorPin2 = 10; // Motor control pin 2 (to L293D Input 2)
const int startSwitch = 53; // Start switch connected to pin 2
const int stopSwitch = 51;  // Stop switch connected to pin 3

// Variables to store motor state
bool motorRunning = true;

void setup() {
  // Set motor pins as output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Set switch pins as input with pull-up resistors
  pinMode(startSwitch, INPUT);
  pinMode(stopSwitch, INPUT);

  // Ensure motor is initially stopped
  startMotor();
}

void loop() {
  // Check if the start switch is pressed
  if (digitalRead(startSwitch) == HIGH) {
    motorRunning = false; // Update motor state
    stopMotor();
    delay(300); // Debounce delay
  }

  // Check if the stop switch is pressed
  if (digitalRead(stopSwitch) == HIGH) {
    motorRunning = false; // Update motor state
    stopMotor();
    delay(300); // Debounce delay
  }
}

void startMotor() {
  // Rotate motor in one direction
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

void stopMotor() {
  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
