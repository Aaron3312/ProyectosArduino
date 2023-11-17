/*********************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *********************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2QbnuTeZN"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "Q2-LWjH3tBweXDRQEJPGYL3O_J3xsM-w"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define DHTPIN 26     // El pin al que está conectado el sensor
#define DHTTYPE DHT11   // Tipo de sensor DHT, puede ser DHT11, DHT21 o DHT22

//el led es 35
//el relay es el d12
//el led interno no existe segun v6?
//• Humedad (V7) – Gauge d26
// temperatura (V2) - D26
//iluminacion (v8) - label



#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


DHT dht(DHTPIN, DHTTYPE);
const int pinSensorLuz = 36;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Xiaomi";
char pass[] = "12345678";
const int pinLedRed = 32; // D32 en el ESP32
bool estadoInterruptor = false;

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  pinMode(pinLedRed, value);

  // Update state
  Blynk.virtualWrite(V1, value);
}




// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  //timer.setInterval(1000L, myTimerEvent);
  Serial.println("DHTxx test!");

  dht.begin();
    pinMode(pinLedRed, INPUT);
}

void loop()
{
  Blynk.run();
  //timer.run();
  int lecturaInterruptor = digitalRead(pinLedRed);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
    // Lectura de la humedad
  if (lecturaInterruptor != estadoInterruptor){
    estadoInterruptor = lecturaInterruptor;

  
  Blynk.virtualWrite(V0, estadoInterruptor);
  }
  float h = dht.readHumidity();
  // Lectura de la temperatura en grados Celsius
  float t = dht.readTemperature();

  // Comprueba si alguna lectura falló y sale temprano (para intentarlo de nuevo).
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT!");
    return;
  }

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
  Serial.println(valorSensorLuz);
  Blynk.virtualWrite(V8, valorSensorLuz);
  Blynk.virtualWrite(V7, h);
  Blynk.virtualWrite(V2, t);
}