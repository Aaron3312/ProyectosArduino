#include <WiFi.h>
#include <FirebaseESP32.h>


/*Define the API Key */
#define API_KEY "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"


#define FIREBASE_HOST "https://iot-robotarm-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "69d147c63f754cf42d66b03b37d10c979d95ec11"
//#define FIREBASE_AUTH "HtgqeSJYyCuBWhwNWAi1EaCFoBeV8T5MNlzyPiaVnVM"
#define WIFI_SSID "Xiaomi"
#define WIFI_PASSWORD "12345678"


// Pines del potenciómetro y el LED RGB
const int pinPotenciometro = 36;
const int pinRojo = 27;
const int pinVerde = 26;
const int pinAzul = 25;
String sdsd = "bro";


// Variables para controlar los colores
int valorPotenciometroDataBase = 0;
int valorPotenciometroBoard = 0;
int valorPotenciometro = 0;
int valorRojo = 0;
int valorVerde = 0;
int valorAzul = 0;
bool valorPots = false;
bool encendido = true;
bool apagado = false;


String nodo = "Proyecto-iot";



FirebaseData firebaseData;

void setup() {
  //codigo del profe
  Serial.begin(115200);
  delay(2000);
  Serial.printf("Inicializando...\n");  
  
  Serial.setDebugOutput(true);


  //esto es codigo de bard

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado a la red WiFi, dirección IP: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //linea profe no se q hace x2
  Firebase.reconnectWiFi(true);
  
  Serial.printf("cela");
  // Sube datos a Firebase

  Firebase.setString(firebaseData, "Led1", "Hola Mundo!");
  //Firebase.setFloat(firebaseData, "/sensor/temperatura", 25.5);
  pinMode(pinPotenciometro, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {


 
 // Lee el valor del potenciómetro
 
 /*
  // Calcula el valor de cada color del LED RGB
  if (valorPotenciometro > 2731) {
    // Valor verde
    ///*
    valorRojo = 0;
    valorVerde = 255;
    valorAzul = 0;
    
    ///*
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, LOW);
    //
  } else if (valorPotenciometro > 1366 && valorPotenciometro <= 2730 ) {
    // Valor azul
    ///*
    valorRojo = 0;
    valorVerde = 0;
    valorAzul = 255;
    //*/
    /*
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, HIGH);
    
  } else if (valorPotenciometro > 0 && valorPotenciometro <= 1365 ) {
    // Valor rojo
    
    valorRojo = 255;
    valorVerde = 0;
    valorAzul = 0;

    /*
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, LOW);
    
  }
  */
  
  valorPotenciometroBoard = analogRead(pinPotenciometro);
  /*
  Firebase.setBool(firebaseData, "Pot", encendido);
  valorPots = Firebase.getBool(firebaseData, "Pot");
  sdsd = Firebase.getString(firebaseData, "Pot");

  
  Serial.print(sdsd);

  Firebase.setInt(firebaseData, "Potenciometro", valorPotenciometro);
  Serial.print(valorPots);

  Firebase.setBool(firebaseData, "Pot", apagado);
  valorPots = Firebase.getBool(firebaseData, "Pot");
  Serial.print(valorPots);
*/
    // Obtiene el valor booleano de Firebase
  if (Firebase.getBool(firebaseData, "Pot")) {
    valorPots = firebaseData.boolData();
    /*
    Serial.print("Valor booleano recibido desde Firebase: ");
    Serial.println(valorPots);
    */
  }
  
  if (valorPots == 0){ //hace la base de datos

    if(Firebase.getInt(firebaseData,"Potenciometro")){
      valorPotenciometroDataBase = firebaseData.intData(); //baja potenciometroData
      /*
      Serial.print("valor int potenciometro data base"); 
      Serial.println(valorPotenciometroDataBase); //imprime potenciometroData
      */
    }
    valorPotenciometro = valorPotenciometroDataBase;
  }

  if (valorPots == 1){ // hace el board
    valorPotenciometro = valorPotenciometroBoard; //iguala el board al potenciometro code
    Firebase.setInt(firebaseData, "Potenciometro", valorPotenciometro); // sube el potenciometro board
  }



/*
  while (valorPots == 1){
    Serial.print("its true man");
    Serial.print(valorPots);
    delay (2000);
    valorPots =  Firebase.setBool(firebaseData, "Pot", apagado);
  }
  */

  valorPotenciometroDataBase = Firebase.getString(firebaseData, "Potenciometro");
  /*
  if (valorPotenciometro != valorPotenciometroDataBase){
    valorPotenciometro = valorPotenciometroDataBase
    delay (10000)
  }
  */

  // Calcula el valor de cada color del LED RGB
  int valorRojo = map(valorPotenciometro, 0, 1365, 0, 255);
  if (valorPotenciometro > 1365){
    valorRojo = 1;
  }
  if (valorPotenciometro == 0){
    valorRojo = 1;
  }
  int valorVerde = map(valorPotenciometro, 1365, 2730, 0, 255);
  if (valorPotenciometro > 2730){
    valorVerde = 1;
  }
  int valorAzul = map(valorPotenciometro, 2730, 4095, 0, 255);
  // Escribe el valor de cada color del LED RGB
  if (valorPotenciometro < 2730){
    valorAzul = 1;
  }
 
  ///*
  analogWrite(pinRojo, valorRojo);
  analogWrite(pinVerde, valorVerde);
  analogWrite(pinAzul, valorAzul);
  //*/


  


  delay(100);
  Serial.println(valorPotenciometro);




}
