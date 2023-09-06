#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <DHT.h>

#define DHT_PIN 10      // Pin connected to the DHT sensor
#define DHT_TYPE DHT11 // DHT sensor type


AF_DCMotor motor1(1);  // Motor 1 initialization
AF_DCMotor motor2(2);  // Motor 2 initialization
AF_DCMotor motor3(3);  // Motor 3 initialization
AF_DCMotor motor4(6);  // Motor 4 initialization

SoftwareSerial bluetooth(2, 3);  // Bluetooth module RX, TX pin

const int trigPin = 4;  // Ultrasonic sensor trigger pin
const int echoPin = 5;
long distance;  // Ultrasonic sensor echo pin
NewPing sonar(trigPin, echoPin);  // Create a NewPing object
DHT dht(DHT_PIN, DHT_TYPE);
void setup() {
  // Set the baud rate for the Bluetooth module
  bluetooth.begin(9600);

  // Initialize the motor driver pins
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  long duration = sonar.ping_median();
  long distance = NewPing::convert_cm(duration);
  Serial.print("Distance: ");
  Serial.print(distance);
  if (Serial.available()) {
    char command = Serial.read();
    Serial.println(command);

    // Control the motors based on the received command
    switch (command) {
      case 'F':
        if(distance>=10)  // Move forward
        moveForward();
        else Serial.println("obstacle! cant move forward");
        break;
      case 'B':  // Move backward
        moveBackward();
        break;
      case 'L':  // Turn left
        turnLeft();
        break;
      case 'R':  // Turn right
        turnRight();
        break;
      case 'S':  // Stop
        stopMotors();
        break;
    }
  }
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity as a percentage

  // Measure the distance using the ultrasonic sensor
  
  if(distance<=3){
     Serial.print("car crashed");
  }
  
  
  Serial.println(" cm");
  Serial.println("lat : 13.0304663 ");
  Serial.println("lan : 77.565336 ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(500);  // Delay between distance measurements
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
