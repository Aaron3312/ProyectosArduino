#include <Servo.h>
int intensidad;
Servo miServo;


void setup() {
  Serial.begin(9600);
pinMode(13,OUTPUT);
miServo.attach(5);
miServo.write(90);

}

void loop() {
 intensidad = analogRead(0);
  Serial.println(intensidad);
  digitalWrite(13,HIGH);

 if(intensidad>525){
  miServo.write(0);
  delay(500);
 }
  else if(intensidad<525){
    miServo.write(90);
    delay(900);
  }

  
}

//Con carro = 750
//Umbral = 525
//Sin carro = 300
