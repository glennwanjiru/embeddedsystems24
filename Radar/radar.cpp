#include <Servo.h>
#include <Arduino.h
#define BUZZER_PIN 12  // Define the pin connected to the buzzer

Servo myservo;
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;

const int stepAngle = 5;
long duration, distance;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
}

void loop() {
  for (int angle = 0; angle <= 180; angle += stepAngle) {
    myservo.write(angle);

    // Delay for 1 second between scans
    delay(200);

    // Trigger measurement
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read echo and calculate distance
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    // Check for obstacle and beep if detected
    if (distance < 50) {
      myservo.write(90);
      Serial.print("Obstacle at angle: ");
      Serial.print(angle);
      Serial.print(" degrees, distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      // Use tone() or digitalWrite() for desired buzzer behavior
      // Option 1: Use tone() for specific frequency and duration
      tone(BUZZER_PIN, 1000, 500); // Beeps at 1kHz for 500ms

      // Option 2: Use digitalWrite() for simple on/off control
      // digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
      // delay(500); // Keep buzzer on for 500ms
      // digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer

      // Optional: Stop servo on obstacle detection
      // myservo.stop(); // uncomment if you want to stop servo
      // break; // uncomment if you want to exit the loop
    }
  }
}