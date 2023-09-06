
#include <SPI.h>

#include <LoRa.h>
int vresistor = A1; // to control the speed of brushless motor
int vrdata = 0;

//Joystick
int Jstick_VRx = A2; // the Joystick VRx pin is connected with the analog pin A2
int Jstick_VRy = A3; // the Joystick VRy pin is connected with the analog pin A3
int UD = 0; // Up and Down
int LR = 0; // Left and Right

int data_length; 
String sensorsdata;

void setup() {
Serial.begin(115200); 
Serial.begin(9600);

  while (!Serial);


  Serial.println("LoRa Sender");


  if (!LoRa.begin(433E6)) {

    Serial.println("Starting LoRa failed!");

    while (1);

  }
pinMode(vresistor,INPUT); 
pinMode(Jstick_VRx,INPUT);
pinMode(Jstick_VRy,INPUT);
}

void loop() {

VRspeed();
up_down();
left_right();
data_to_receiver();


}




void VRspeed()// to control the speed of Brushless motor
{
 vrdata = analogRead(vresistor); // Potentiometer or Variable resistor is connected with Analog pin A1
 vrdata = map(vrdata, 0, 1023,100,1023); 
 if (vrdata < 100)
 {
  vrdata = 100;
 }
  if (vrdata > 1023)
 {
  vrdata = 1023;
 }
 
delay(10);

}

void up_down()
{
 UD = analogRead(Jstick_VRx); 
 if ( UD < 100) 
 {
  UD = 100;
 }
delay(10);

}

void left_right()
{
 LR = analogRead(Jstick_VRy); 
 if ( LR < 100 )
 {
  LR = 100;
 }
delay(10);
}

void data_to_receiver()
{
 sensorsdata = sensorsdata + vrdata + "%" + UD + "%" + LR; 
 //Serial.println(vrdata);
// find the length of data
 data_length = sensorsdata.length();
 //Serial.println("data length:"); 
 //Serial.println(data_length); 
 send_data(sensorsdata , data_length); 
delay(1000); 
sensorsdata = ""; // empty the variable  
  
}

void send_data(String sensorvalue, int valuelength)
{

String mymessage; 
mymessage = mymessage + sensorvalue + "\r"; 
Serial.println(mymessage);
Serial.println("Sending packet: ");

  //Serial.println(counter);


  // send packet

  LoRa.beginPacket();

  LoRa.print(mymessage);

  //LoRa.print(counter);

  LoRa.endPacket();


  //counter++;


  delay(1000);
//lora(mymessage); 
  //Serial.println("AT+SEND=0,6,Hello!\r");
}