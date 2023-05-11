#include <WiFi.h>
#include "Adafruit_MQTT.h"

// credenciales del wifi
const char* ssid = "XXXXXX";
const char* password = "XXXXXX";

// variables de conexión con adafruit
#define IO_USERNAME  "XXXXXX"
#define IO_KEY       "XXXXXX"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
const char* topic = "XXXXXX";

// inicialización de variables 
int valor = 0;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, topic);
      
void setup() {
  Serial.begin(9600);
  delay(10);

  // conectar al wifi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");
  
  // conectar a adafruit por mqtt
  mqtt.connect();
  while (!mqtt.connected()) {
    delay(1000);
    Serial.println("Conectando a Adafruit IO MQTT...");
    mqtt.connect();
  }

  Serial.println("Conectado a Adafruit IO MQTT");

}

void loop() {  
  feed.publish(valor);
  Serial.println("Envia el dato al servidor");
  Serial.println(valor);
  valor = valor + 1;
  delay(2000);
}
