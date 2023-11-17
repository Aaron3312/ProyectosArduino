// Definir los pines para el LED RGB
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

// Definir el pin del potenciómetro
int potPin = A0;

void setup() {
  // Configurar los pines del LED RGB como salidas
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Iniciar la comunicación serial a una velocidad de 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Leer el valor del potenciómetro
  int potVal = analogRead(potPin);

  // Imprimir el valor del potenciómetro
  Serial.print("Valor del potenciometro: ");
  Serial.println(potVal);

  // Mappear el valor del potenciómetro al rango de 0-255
  int val = map(potVal, 0, 1023, 0, 255);

  // Cambiar el color del LED RGB en función del valor del potenciómetro
  if (val <= 85) {
    // Cambiar a color rojo
    analogWrite(redPin, val * 3);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else if (val <= 170) {
    // Cambiar a color verde
    analogWrite(redPin, 0);
    analogWrite(greenPin, val * 3 - 255);
    analogWrite(bluePin, 0);
  } else {
    // Cambiar a color azul
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, val * 3 - 510);
  }

  // Esperar un breve periodo de tiempo antes de repetir
  delay(10);
}
