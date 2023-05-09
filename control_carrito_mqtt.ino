//Libreria para podernos conectar el dispositivo a Internet

//por Wi-Fi

#include <WiFi.h>

//Libreria para podernos conectar al broker MQTT

#include <PubSubClient.h>

//Pines del motor
int motorA1=15;
int motorA2=2;
int motorB1=0;
int motorB2=4;

//Constantes para conectarnos a la red Wi-Fi mediante ssid y su contraseña

const char* ssid = "Yisus";

const char* password = "burritouwu";

 

//Dirección del broker MQTT

const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;

PubSubClient client(espClient);

 
//Funcion para conectarse a una red WiFi
void setup_wifi() {

  delay(10);

  // Empezamos por conectarnos a una red WiFi

  Serial.println();

  Serial.print("Conectado a ");

  Serial.println(ssid);

 

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

 

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

 

  randomSeed(micros());

 

  Serial.println("");

  Serial.println("WiFi conectado");

  Serial.println("Dirección IP: ");

  Serial.println(WiFi.localIP());

}

 
// Función de devolución de llamada (callback) cuando un mensaje MQTT es recibido
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Llegó el mensaje del tema [");

  Serial.print(topic);

  Serial.print("] ");

 

  String message;

  for (int i = 0; i < length; i++) {

    message = message + (char) payload[i];  // convert *byte to string

    Serial.print((char)payload[i]);

  }

  Serial.println();

  Serial.print(message);

 

  // Interpretar los mensajes recibidos
  if(message=="adelante")

  {

  adelante(); // llamamos a la funcion adelante para mover el carrito      

  Serial.println();  

  Serial.println("el carrito avanzo ");

  }

 

  if(message=="izquierda")

  {

  izquierda();   // llamamos a la funcion izquierda para mover el carrito     

  Serial.println("carrito giro a la derecha");

  }
  if(message=="derecha")

  {

  derecha();   // llamamos a la funcion derecha para mover el carrito     

  Serial.println("carrito giro a la derecha");

  }
  if(message=="atras")

  {

   atras();   // llamamos a la funcion atras para mover el carrito     

  Serial.println("carrito retrocedio ");

  }
  if(message=="detener")

  {

  detener(); // llamamos a la funcion detener para mover el carrito          

  Serial.println();  

  Serial.println("el carrrito se detuvo");

  }


}

 

// Función para conectarse al broker MQTT
void reconnect() {

  // Bucle hasta que nos volvamos a conectar

  while (!client.connected()) {

    Serial.print("Intentando la conexión MQTT...");

    // Crea una identificación de cliente aleatoria

    String clientId = "ESP8266Client-";

    clientId += String(random(0xffff), HEX);

    // Intenta conectarse

    if (client.connect(clientId.c_str())) {

      Serial.println("conectado");

      // Una vez conectado, publique un anuncio...

      client.publish("gmcr/led", "hello world");

      // ... y volver a suscribirte

      client.subscribe("gmcr/acciones");

    } else {

      Serial.print("fallido, rc =");

      Serial.print(client.state());

      Serial.println("inténtalo de nuevo en 5 segundos");

      // Espere 5 segundos antes de volver a intentarlo

      delay(5000);

    }

  }

}

void setup() {
  // Poner los pines de los motores en salidas
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  Serial.begin(115200);

  //Llamar a la funcion setup_wifi para conectarse a internet
  setup_wifi();

  //llamar al servidor y el puerto MQTT
  client.setServer(mqtt_server, 1883);

  //Llamar a la funcion callback
  client.setCallback(callback);

}

void loop() {
  //Si el cliente se conecta, llamar a funcion reconnect
  if (!client.connected()) {

    reconnect();

  }
  //Bucle para que el cliente siga publicando o suscribiendo mensajes
  client.loop();
 
}

//Funcion adelante para mover el carrito, indicando que pines de los motores se deben activar
void adelante(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
  delay(1000);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
//Funcion detener para parar el carrito, indicando que pines de los motores se deben desactivar
void detener(){
   //detener
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
//Funcion atras para mover el carrito, indicando que pines de los motores se deben activar
void atras(){
  //motor hacia atras
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(1000);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
//Funcion izquierda para mover el carrito, indicando que pines de los motores se deben activar
void izquierda(){
   //IZQUIERDA:
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
  delay(500);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
//Funcion derecha para mover el carrito, indicando que pines de los motores se deben activar
void derecha(){
   //DERECHA
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(500);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
