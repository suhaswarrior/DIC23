#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
#define NUM_FLAME_SENSORS 5

int flameSensorPins[NUM_FLAME_SENSORS] = {A0, A1, A2, A3, A4};
int flameThreshold = 500;
int fireMotorPin1 = 7;


int iterationCount = 0;

void setup() {
  motor1.attach(8);  // Connect motor1 to PWM pin 9
  motor2.attach(9); // Connect motor2 to PWM pin 10
  motor3.attach(10); // Connect motor3 to PWM pin 11
  motor4.attach(11); // Connect motor4 to PWM pin 12
  motor5.attach(12); // Connect motor5 to PWM pin 13
 
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7,HIGH);
  // Control motor1 in the range of 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos+=10) {
    motor1.write(pos);
    delay(15); // Adjust the delay for desired speed
    for (int i = 0; i < NUM_FLAME_SENSORS; i++) {
      if (detectFlame(flameSensorPins[i])) {
        extinguishFire();
      }
    } // Adjust the delay for desired speed

    
    
      // Control motor2 in the range of 60 to 120 degrees
      for (int i = 150; i >= 120; i--) {
        motor2.write(i);
        delay(15);
        for (int i = 0; i < NUM_FLAME_SENSORS; i++) {
      if (detectFlame(flameSensorPins[i])) {
        extinguishFire();
      }
      }
      }
  
      // Control motor3 in the range of 0 to 70 degrees
      for (int i = 40; i <= 70; i++) {
        motor3.write(i);
        delay(15);
        for (int i = 0; i < NUM_FLAME_SENSORS; i++) {
      if (detectFlame(flameSensorPins[i])) {
        extinguishFire();
      }
    }
      }
  
      // Control motor4 in the range of 180 to 135 degrees
      for (int i = 180; i >= 150; i--) {
        motor4.write(175);
        delay(15);
        for (int i = 0; i < NUM_FLAME_SENSORS; i++) {
      if (detectFlame(flameSensorPins[i])) {
        extinguishFire();
      }
    }
      }
  
      // Control motor5 in the range of 180 to 150 degrees
      for (int i = 180; i >= 150; i--) {
        motor5.write(165);
        delay(15);
        for (int i = 0; i < NUM_FLAME_SENSORS; i++) {
      if (detectFlame(flameSensorPins[i])) {
        extinguishFire();
      }
    }
      }
    }

  
  // Reset positions of all motors
 //ait for 1 second before repeating the sequence
 
}

 bool detectFlame(int pin) {
  int flameValue = analogRead(pin);
  return (flameValue > flameThreshold);
}

void extinguishFire() {
  digitalWrite(fireMotorPin1, HIGH);
  
  delay(1000);
  digitalWrite(fireMotorPin1, LOW);
  

}


