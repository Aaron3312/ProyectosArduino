/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2TJdyJbBK"
#define BLYNK_TEMPLATE_NAME "LEDStart"
#define BLYNK_AUTH_TOKEN "lTRW5zlbEu8DhSosIMC-UlxH1gh21cEO"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define LED_PIN 4
#define APP_DEBUG


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Don Panelo y su pandilla";
char pass[] = "Purrrfecto#Miaw#";


BLYNK_WRITE(V0)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();

  if (value == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("value =");
    Serial.println(value);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("value = ");
    Serial.println(value);
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(LED_PIN, OUTPUT);

  delay(100);


}

void loop()
{
  Blynk.run();
  delay(10);  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!


}
