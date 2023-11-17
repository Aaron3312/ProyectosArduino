#include <DHT.h>

//el led es 35
//el relay es el d12
//el led interno no existe segun v6?
//• Humedad (V7) – Gauge d26
// temperatura (V2) - D26
//iluminacion (v8) - label



#define DHTPIN 26     // El pin al que está conectado el sensor
#define DHTTYPE DHT11   // Tipo de sensor DHT, puede ser DHT11, DHT21 o DHT22

DHT dht(DHTPIN, DHTTYPE);
const int pinSensorLuz = 36; // Pin A0 en el ESP32 para el sensor de luz
 

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Espera un momento entre las lecturas
  delay(2000);

  // Lectura de la humedad
  float h = dht.readHumidity();
  // Lectura de la temperatura en grados Celsius
  float t = dht.readTemperature();

  // Comprueba si alguna lectura falló y sale temprano (para intentarlo de nuevo).
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT!");
    return;
  }

  // Imprimir los valores de temperatura y humedad en el Monitor Serie
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
    // Leer el valor analógico del sensor de luz
  int valorSensorLuz = analogRead(pinSensorLuz);

  // Imprimir el valor leído en el monitor en serie
  Serial.print("Valor del sensor de luz: ");
  Blynk.virtualWrite(V8, valorSensorLuz);
  Blynk.virtualWrite(V7, h);
  Blynk.virtualWrite(v2, t);
}
