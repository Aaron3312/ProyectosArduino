#include <WiFi.h>


// Definiciones de pines usados para los motores
#define PIN_MOTOR_R_FWD 5
#define PIN_MOTOR_R_BWD 18
#define PIN_MOTOR_L_FWD 19
#define PIN_MOTOR_L_BWD 21      

// Definiciones de pines para el sensor de proximidad ultrasónico
#define TRIGGER_PIN 4
#define ECHO_PIN 2

enum Comandos { CMD_FORWARD = 'w', CMD_BACKWARD ='s', CMD_RIGHT ='d', CMD_LEFT = 'a', CMD_STOP = 'q' }; // Enumeración de comandos recibidos


//Configuración de red
const char* ssid     = "Xiaomi";
const char* password = "12345678";

WiFiServer TCPServer(8266); //Servidor del ESP32
WiFiClient TCPClient; //Cliente TCP (PC)

// Función para manejar la detección del sensor de proximidad
bool detectar_obstaculo() {
    long duration, distance;
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration / 2) / 29.1;
    return distance < 10; // Ajusta el valor de distancia según tus necesidades
}

void byteReceived(byte byteReceived) {    
    

    switch(byteReceived){

      case CMD_FORWARD:
       Serial.println("Forward");
       digitalWrite(PIN_MOTOR_R_FWD, HIGH);
       digitalWrite(PIN_MOTOR_R_BWD, LOW);
       digitalWrite(PIN_MOTOR_L_FWD, HIGH);
       digitalWrite(PIN_MOTOR_L_BWD, LOW);

      break;

      case CMD_BACKWARD:

      Serial.println("Backward");
       digitalWrite(PIN_MOTOR_R_FWD, LOW);
       digitalWrite(PIN_MOTOR_R_BWD, HIGH);
       digitalWrite(PIN_MOTOR_L_FWD, LOW);
       digitalWrite(PIN_MOTOR_L_BWD, HIGH);
      
      break;

      case CMD_RIGHT:

       Serial.println("Right");
       digitalWrite(PIN_MOTOR_R_FWD, LOW);
       digitalWrite(PIN_MOTOR_R_BWD, HIGH);
       digitalWrite(PIN_MOTOR_L_FWD, HIGH);
       digitalWrite(PIN_MOTOR_L_BWD, LOW);

      break;


      case CMD_LEFT:
       Serial.println("Left");
       digitalWrite(PIN_MOTOR_R_FWD, HIGH);
       digitalWrite(PIN_MOTOR_R_BWD, LOW);
       digitalWrite(PIN_MOTOR_L_FWD, LOW);
       digitalWrite(PIN_MOTOR_L_BWD, HIGH);

      break;
      case CMD_STOP:

        Serial.println("Stop ");
      
        digitalWrite(PIN_MOTOR_R_FWD, LOW);
        digitalWrite(PIN_MOTOR_R_BWD, LOW);
        digitalWrite(PIN_MOTOR_L_FWD, LOW);
        digitalWrite(PIN_MOTOR_L_BWD, LOW);

      break;

      default: break;
            
    }
  
}

void setup() {

  pinMode(PIN_MOTOR_R_FWD, OUTPUT);
  pinMode(PIN_MOTOR_R_BWD, OUTPUT);
  pinMode(PIN_MOTOR_L_FWD, OUTPUT);
  pinMode(PIN_MOTOR_L_BWD, OUTPUT);

  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(PIN_MOTOR_R_FWD, LOW);
  digitalWrite(PIN_MOTOR_R_BWD, LOW);
  digitalWrite(PIN_MOTOR_L_FWD, LOW);
  digitalWrite(PIN_MOTOR_L_BWD, LOW);
  
  Serial.begin(115200);

  Serial.printf("Conectando a: %s\n", ssid);
 
  WiFi.begin(ssid, password);
  
  // Intentamos que se conecte a la red wifi
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando...");
    delay(2000);
    }
  
  Serial.print("Conectado.  ");
  Serial.print(" Dirección IP del módulo: ");
  Serial.println(WiFi.localIP());

 TCPServer.begin();
      

}

void loop() {

   /*if (Serial.available() > 0)
       byteReceived(Serial.read());*/

    if (!TCPClient.connected()) {
        // try to connect to a new client
        TCPClient = TCPServer.available();
    } else {
        // read data from the connected client
        if (TCPClient.available() > 0) {
            byteReceived(TCPClient.read());
                                                                                                                                                                                                                                                                                                                                                                                 
            
        }
    }

        // Detección de proximidad
    if (detectar_obstaculo()) {
        Serial.println("Obstáculo detectado. Deteniendo el carro.");
        byteReceived(CMD_STOP);
    }

}