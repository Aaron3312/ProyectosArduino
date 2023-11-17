
// Definiciones de pines usados para los motores
#define PIN_MOTOR_R_FWD 5
#define PIN_MOTOR_R_BWD 18
#define PIN_MOTOR_L_FWD 19
#define PIN_MOTOR_L_BWD 21      


enum Comandos { CMD_FORWARD = 'w', CMD_BACKWARD ='s', CMD_RIGHT ='d', CMD_LEFT = 'a', CMD_STOP = 'q' }; // Enumeración de comandos recibidos



void byteReceived() {
  
    
    char byteRecibido = (char)Serial.read();

    switch(byteRecibido){

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

  digitalWrite(PIN_MOTOR_R_FWD, LOW);
  digitalWrite(PIN_MOTOR_R_BWD, LOW);
  digitalWrite(PIN_MOTOR_L_FWD, LOW);
  digitalWrite(PIN_MOTOR_L_BWD, LOW);
  
  Serial.begin(115200);

}

void loop() {

   if (Serial.available() > 0)
       byteReceived();
}