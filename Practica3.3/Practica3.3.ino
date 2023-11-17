#include <WiFi.h>
#include <FirebaseESP32.h>

// Configuración de Wi-Fi
const char* ssid = "Xiaomi";
const char* password = "12345678";

// Configuración de Firebase
const char* projectID = "69d147c63f754cf42d66b03b37d10c979d95ec11";
const char* apiKey = "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74";
const char* authDomain = "https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F";
const char* databaseURL = "https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F";

FirebaseConfig config;
FirebaseAuth auth;

config.setProjectID(projectID);
config.setAPIKey(apiKey);
config.setAuthDomain(authDomain);
config.setDatabaseURL(databaseURL);



#define API_KEY "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"

#define FIREBASE_HOST "https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F"
#define FIREBASE_AUTH "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"

#define WIFI_SSID "Xiaomi"
#define WIFI_PASSWORD "12345678"

// Objeto Firebase
FirebaseData firebaseData;

void setup() {
  // Inicializa la conexión Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Inicializa Firebase
Firebase.begin(config, auth);
}

void loop() {
  // Comprueba la conexión a Firebase
  if (firebaseData.connected()) {
    // Escribe un dato en la base de datos
    Firebase.setString(firebaseData, "/data/value", "Hola, Firebase!");

    // Lee un dato de la base de datos
    String value = Firebase.getString(firebaseData, "/data/value");
    Serial.println(value);
  } else {
    Serial.println("No se puede conectar a Firebase.");
  }

  delay(1000);
}
