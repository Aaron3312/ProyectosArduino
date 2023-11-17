
#define BLYNK_TEMPLATE_ID           "TMPL2QbnuTeZN"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "Q2-LWjH3tBweXDRQEJPGYL3O_J3xsM-w"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Credenciales de red WiFi
char auth[] = "Q2-LWjH3tBweXDRQEJPGYL3O_J3xsM-w";
char ssid[] = "Xiaomi";
char pass[] = "12345678";


/* Fill-in information from Blynk Device Info here */

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Pin del interruptor físico
const int pinInterruptor = 32; // D32 en el ESP32

// Variable para almacenar el estado del interruptor
int estadoInterruptor = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pinInterruptor, INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  // Leer el estado del interruptor físico
  int lecturaInterruptor = digitalRead(pinInterruptor);

  // Si el estado del interruptor ha cambiado
  if (lecturaInterruptor != estadoInterruptor) {
    // Actualizar el estado del interruptor
    estadoInterruptor = lecturaInterruptor;

    // Enviar el estado al pin virtual V0 en Blynk
    Blynk.virtualWrite(V0, estadoInterruptor);
  }
  //int s0 = Blynk.virtual(V0);
  //Serial.out(s0);
}

