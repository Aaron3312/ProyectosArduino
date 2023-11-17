/*********
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <SoftwareSerial.h>


// Configure software serial port
SoftwareSerial SIM900(7, 8);

char caracter; // caracter que optenemos?
//Variable to save incoming SMS characters
char incoming_char=0;

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // For serial monitor
  Serial.begin(19200); 
  // Give time to your GSM shield log on to network
  delay(10000);
}

void loop() {
  if (SIM900.available()){//si hay caracteres
    caracter = SIM900.read();
    Serial.print(caracter);
  }
  if (Serial.available()){
    caracter = Serial.read();
    SIM900.print(caracter);
  }
}