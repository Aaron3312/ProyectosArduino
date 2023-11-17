#include <DHT.h>
#include <DHT_U.h>
#define Type DHT11
int sensorPin = 10; 
int ledPin = 11;
int ledRojo = 12;
int ledAzul = 13;

const int triggerPin = 2;
const int echoPin = 3;
int dhtPin=9; // Pin analógico donde se conecta el sensor
DHT HT(dhtPin, Type);
int humidity;
float tempC;
float tempF;

const int ledPin1 = 8; 
const int ledPin2 = 7;
const int ledPin3 = 6;
const int ledPin4 = 5;
const int ledPin5 = 4;

void setup() {
  Serial.begin(9600); // Inicializamos la comunicación serial
  pinMode(triggerPin, OUTPUT); // Configuramos el pin trigger como salida
  pinMode(echoPin, INPUT); // Configuramos el pin echo como entrada
  HT.begin();
  pinMode(ledRojo,OUTPUT);
  pinMode(ledAzul,OUTPUT);

  pinMode(sensorPin, INPUT); // Se configura el pin del sensor como entrada
  pinMode(ledPin, OUTPUT); // Se configura el pin del LED como salida
  Serial.begin(9600); // Se inicia la comunicación serial

  pinMode(ledPin1, OUTPUT); // Configuramos los pines de los LEDs como salida
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}


void loop() {
  int movimiento = digitalRead(sensorPin); // Se lee el valor del sensor

  if (movimiento == HIGH) { // Si el sensor detecta movimiento
    digitalWrite(ledPin, HIGH); // Se enciende el LED
    Serial.println("Movimiento detectado"); // Se imprime en el monitor serial
  } else { // Si el sensor no detecta movimiento
    digitalWrite(ledPin, LOW); // Se apaga el LED
    Serial.println("No hay movimiento"); // Se imprime en el monitor serial
  }
  digitalWrite(triggerPin, LOW); // Enviamos un pulso bajo al pin trigger
  delayMicroseconds(2); // Esperamos un momento
  digitalWrite(triggerPin, HIGH); // Enviamos un pulso alto al pin trigger
  delayMicroseconds(10); // Esperamos un momento
  digitalWrite(triggerPin, LOW); // Enviamos otro pulso bajo al pin trigger

  long duration = pulseIn(echoPin, HIGH); // Medimos la duración del pulso en el pin echo
  float distance = duration * 0.034 / 2; // Calculamos la distancia en cm

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Encendemos los LEDs en base a la distancia detectada
  if (distance >= 4) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }
  
  if (distance >= 5) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }
  
  if (distance >= 6) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin3, LOW);
  }
  
  if (distance >= 8) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  } else {
    digitalWrite(ledPin4, LOW);
  }
  
  if (distance >= 10) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, HIGH);
  } else {
    digitalWrite(ledPin5, LOW);
  }
   // Convertimos el voltaje a temperatura en grados Celsius

  humidity=HT.readHumidity();
  tempC=HT.readTemperature();
  tempF=HT.readTemperature(true);
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.println("°C");
  if (tempC > 30 ){
    digitalWrite(ledRojo,0);
  digitalWrite(ledAzul,255);
  }
  if(tempC < 30){
  digitalWrite(ledRojo,255);
  digitalWrite(ledAzul,0);
  }


  delay(1500); // Esperamos un momento antes de tomar otra medición
}
