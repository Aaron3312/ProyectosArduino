#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definir los pines y nombres de los servos
int servoPins[4] = {0, 1, 2, 4};  
String servoNames[4] = {"Base", "Shoulder", "Elbow", "Gripper"};
int servoMin = 150;  // valor mínimo del pulso para el servo
int servoMax = 600;  // valor máximo del pulso para el servo

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(60);  // Establecer la frecuencia PWM en 60 Hz

  // Mostrar las instrucciones en el monitor serie
  Serial.println("Control de brazo robot con PCA9685");
  Serial.println("Use el formato 'servoIndex valor' para controlar el brazo.");
  Serial.println("Por ejemplo, '0 300' para el servo Base a 300.");
}

void loop() {
  if (Serial.available() > 0) {
    // Leer el comando desde el monitor serie
    String command = Serial.readStringUntil('\n');
    int servoIndex = command.substring(0, command.indexOf(' ')).toInt();
    int value = command.substring(command.indexOf(' ') + 1).toInt();

    // Verificar si el índice del servo y el valor están dentro del rango
    if (servoIndex >= 0 && servoIndex < 4 && value >= servoMin && value <= servoMax) {
      pwm.setPWM(servoPins[servoIndex], 0, value);
      Serial.println("Moviendo el servo " + servoNames[servoIndex] + " a " + String(value));
    } else {
      Serial.println("Comando no válido. Use el formato 'servoIndex valor'.");
    }
  }
}
