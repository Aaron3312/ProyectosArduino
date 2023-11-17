int sensorPin = 2; // Se define el pin de entrada del sensor
int ledPin = 13; // Se define el pin de salida del LED

void setup() {
  pinMode(sensorPin, INPUT); // Se configura el pin del sensor como entrada
  pinMode(ledPin, OUTPUT); // Se configura el pin del LED como salida
  Serial.begin(9600); // Se inicia la comunicación serial
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
  delay(2000); // Se agrega un pequeño retraso para evitar lecturas erróneas
}
