#define BLYNK_TEMPLATE_ID "TMPL2on0UT4O2"
#define BLYNK_TEMPLATE_NAME "LED ESP32"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial

#define APP_DEBUG

#define LED_PIN 5  // Use pin 2 for LED (change it, if your board uses another pin)


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Credenciales de red WiFi
char auth[] = "TMPL2on0UT4O2";
char ssid[] = "Xiaomi";
char pass[] = "12345678";

void setup()
{
  // Iniciar la comunicación serial para depuración
  Serial.begin(115200);

  // Conectar a la red WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");

  // Iniciar la comunicación con el servidor Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  // Ejecutar Blynk
  Blynk.run();
}