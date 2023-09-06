#include <LoRa.h>

// Long Range RC Plane Receiver Side Programming
// https://www.electroniclinic.com/

#include <Servo.h>
#include <SPI.h>

#include <LoRa.h>



Servo servoLeft;
Servo servoRight;

String myString; 
String garbage;
char data; 

int receive_flag = 0; 
// for brushless motor
int Bmotor = 3; // the brushless motor speed controller pwm wire is connected with D1. 
int LeftServo = 5;
int RightServo = 9;

int updownFlag = 0;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

  while (!Serial);


  Serial.println("LoRa Receiver");


  if (!LoRa.begin(433E6)) {

    Serial.println("Starting LoRa failed!");

    while (1);

  } 

servoLeft.attach(LeftServo);
servoRight.attach(RightServo);
servoLeft.write(90);
servoRight.write(90);
delay(2000);
analogWrite(Bmotor,0);
Serial.print("AT\r\n");

delay(100); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    // received a packet

    Serial.print("Received packet '");


    // read packet

    while (LoRa.available()) {

      Serial.print((char)LoRa.read());

    }
     // print RSSI of packet

    Serial.print("' with RSSI ");

    Serial.println(LoRa.packetRssi());
    



 
  garbage = (char)LoRa.read(); // consists of the +ERR=2 ERROR. 
  
  myString = (char)LoRa.read(); 
  //Serial.println(myString); 

  //Serial.println("Garbage:");
  //Serial.println(garbage);

//String l = getValue(myString, ',', 0); // address
//String m = getValue(myString, ',', 1); // data length
String n = getValue(myString, ',', 2); // data
//String o = getValue(myString, ',', 3); //RSSI
//String p = getValue(myString, ',', 4); //SNR

//Serial.println("Address:"); 
//Serial.println(l); 
//
//Serial.println("data length:"); 
//Serial.println(m);
//
//Serial.println("Data:"); 
//Serial.println(n);
//
//Serial.println("RSSI:"); 
//Serial.println(o);
//
//Serial.println("SNR:"); 
//Serial.println(p);

// now i am going to split the data string n which consists of the Sensors values
// in this string sensors values are separated by the % sign. 

String q = getValue(n, '%', 0); // speed
String r = getValue(n, '%', 1); // up and down
String s = getValue(n, '%', 2); // left and right

if ((q == "") || ( r == "") || (s == ""));
int Fspeed = q.toInt(); // Speed
int UpDown = r.toInt(); // Up and Down control
int LeftRight = s.toInt(); // Left and Right control


Serial.println(Fspeed); // speed
Serial.println(UpDown); // up and down
Serial.println(LeftRight); // left and right


Fspeed = map(Fspeed, 100, 1023, 0, 255); 
if( Fspeed > 255)
{
  Fspeed = 255;
}


analogWrite(Bmotor,Fspeed); 
delay(10); 

if (( UpDown > 490) && (UpDown < 510))
{
  servoLeft.write(90);
  servoRight.write(90);
  delay(100);
}

if (UpDown > 600 )
{
  servoLeft.write(180);
  servoRight.write(10);
  delay(100);
}

if (UpDown < 300 )
{
  servoLeft.write(10);
  servoRight.write(180);
  delay(100);
}


if (LeftRight > 600 )
{
  servoRight.write(10);
  delay(500);
}

if ( LeftRight < 300 )
{
  servoLeft.write(10);
  delay(500);

}


//myString = ""; 
//Serial.print("AT\r\n");
}
}



  



String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}