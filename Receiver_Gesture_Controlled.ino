/*
Receiver Hand Gesture Controlled Robot
by:Papuav
instagram: papua_tronics
youtube: Papuav

*/

//Library Needed
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Motor Connection to The Digital pins
int enA = 0;  
int Motor1 = 3;
int Motor2 = 4;
int enB = 1;  
int Motor3 = 5;
int Motor4 = 6;


RF24 radio(8,9); // CE, CSN Connection in Digital Pins
const byte address[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis;
int joystick[2]; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Motor3, OUTPUT);
  pinMode(Motor4, OUTPUT);

  //Set NRF24l01 to Receiver Mode 
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  //Initial state of the Motors
  digitalWrite(Motor1, 0);
  digitalWrite(Motor2, 0);
  digitalWrite(Motor3, 0);
  digitalWrite(Motor4, 0);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
if (radio.available()) {   // If the NRF240L01 module received data
     
    radio.read( joystick, sizeof(joystick) );

    xAxis = joystick[0];
    yAxis = joystick[1];

  //Turn left  
  if ( yAxis > 30 & yAxis < 90) {

  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, HIGH);     
    
  }

  //Turn Right
  else if (yAxis > 260 & yAxis < 330) {

  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);  
    
  }
  
 //Move Backward
 else if (xAxis > 30 & xAxis < 90) {
  
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, HIGH);  
    
  }




  //Move Forward
  else if (xAxis > 260 & xAxis < 335) {

  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);  
  

}

  //Stop Moving
  else {

  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);  
}
    
    Serial.print("xAxis:");
    Serial.println(xAxis);
    delay(20);
    Serial.print("yAxis:");
    Serial.println(yAxis);
    delay(20);
    
}
  //If The Receiver Does not Connect to the Transmitter
  else {

  digitalWrite(Motor1,LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);  
  
  Serial.println("Not Connected!");
  delay(15);  
    }
}
