#include <Servo.h>
=
#define ENZYME_SENSOR_PIN A0  
#define SERVO_PIN 9           

// the threshold is set based on the output of the random forest 
const int ENZYME_THRESHOLD = 500; 


Servo servo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach the servo motor to the specified pin
  servo.attach(SERVO_PIN);

  // Set servo to initial position (0 degrees)
  servo.write(0);
  Serial.println("System ready.");
}

void loop() {
  int enzymeConcentration = analogRead(ENZYME_SENSOR_PIN);
  Serial.print("Enzyme Concentration: ");
  Serial.println(enzymeConcentration);

    if (enzymeConcentration > ENZYME_THRESHOLD) {
    // Turn the servo motor to 90 degrees
    Serial.println("Threshold exceeded. Rotating servo to 90 degrees.");
    servo.write(90);

 
    delay(5000);

 
    servo.write(0);
    Serial.println("Servo reset to 0 degrees.");
  }

  delay(1000);
}