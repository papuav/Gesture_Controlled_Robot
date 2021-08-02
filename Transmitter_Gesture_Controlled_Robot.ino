/*
Transmitter Hand Gesture Controlled Robot
by:Papuav
instagram: papua_tronics
youtube: Papuav

*/

//Library needed
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Wire.h>


RF24 radio(7,8); // CE, CSN Connection in  Digital Pins
const byte address[6] = "00001";
char xyData[32] = "";
int joystick[2];
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

int x;
int y;
int z;
 


void setup(){
  
  //MPU6050 gyroscope Setup
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  //NRF24l01 Wireless Transmitter Setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  Serial.begin(9600);
}

//Code for The MPU6050
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  joystick[0] = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  joystick[1] = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       
  radio.write( joystick, sizeof(joystick) );
  
  Serial.print("AngleX= ");
  Serial.println(joystick[0]);

  Serial.print("AngleY= ");
  Serial.println(joystick[1]);   
  delay(30);
}
