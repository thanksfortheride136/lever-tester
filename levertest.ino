#include <Servo.h>

const int trig_pin = 10;
const int echo_pin = 9;
const int motor_pin = 11;

float duration, distanceToTarget;

Servo motor;

void setup() {
  motor.attach(motor_pin);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  distanceToTarget = getDistance();

  if (distanceToTarget > 0 && distanceToTarget <= 3.0) {
    Serial.println("Object detected within 3 inches. Nudging servo...");

    motor.write(70);  // Forward motion
    delay(300);
    motor.write(110); // Backward motion
    delay(300);
    motor.write(90);  // Stop

    delay(500); // Prevent immediate repeat
  }

  delay(10); // Rapid polling
}

float getDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH, 10000); // 10ms timeout

  if (duration == 0) {
    return -1; // No reading
  }

  float inches = duration * 0.0133 / 2.0; // Simplified inches conversion
  Serial.print("Distance: ");
  Serial.println(inches);
  return inches;
}
