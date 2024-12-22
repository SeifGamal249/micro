#include "HX711.h"

// Pin definitions
const int LOADCELL_DOUT_PIN = 40; // Data pin (DT)
const int LOADCELL_SCK_PIN = 38;  // Clock pin (SCK)

// Initialize HX711
HX711 scale;

void setup() {
  Serial.begin(9600); // Start serial communication
  Serial.println("HX711 Weight Measurement");

  // Initialize the scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Calibration factor (adjust based on your calibration)
  scale.set_scale(2280.f); // Set the calibration factor
  scale.tare();            // Reset the scale to 0
}

void loop() {
  if (scale.is_ready()) {
    // Read the weight in grams
    float weight = scale.get_units(10); // Average of 10 readings
    Serial.print("Weight: ");
    Serial.print(weight, 2); // Print with two decimal places
    Serial.println(" g");
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000); // Wait for 1 second before next reading
}
