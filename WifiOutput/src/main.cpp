/*
 * Program: Controle de uma saída via rede
 * Author: BAPDS
 * Created: 30/03/2018
 * Informações obtidas:
https://www.usinainfo.com.br/blog/esp32-wifi-comunicacao-com-a-internet/
acessado em 07/04/2020 as 18:07
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>

int rele = 0;
int led1 = 1;
int led2 = 2;
int led3 = 3;
int led4 = 4;

int tempo = 1000;
const char* ssid = "CasaBr";
const char* password = "5d8d992e43";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = -3600*3;

WiFiServer server(80);

void piscar(int pino, int vezes) {

  for(int n = 0; n <= vezes; n++){
    digitalWrite(pino, HIGH);
    delay(tempo);
    digitalWrite(pino, LOW);
    delay(tempo);
  }
}

void ligar(int pino) {
    digitalWrite(pino, HIGH);
    delay(tempo);
}

void desligar(int pino) {
    digitalWrite(pino, LOW);
    delay(tempo);
}
/*
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
*/

void setup() {  
  
  Serial.begin(9600); 

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(rele, OUTPUT);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    piscar(led4,1);
    delay(500);
    Serial.print("-");
  }
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // printLocalTime();
  // piscar(led3, 2);
  
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
}

// the loop routine runs over and over again forever:
void loop() {  
  WiFiClient client = server.available();
  
  ligar(led3);
  
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      // desligar(led2);
      // ligar(led1);

      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("WiFi conectada.");
            client.println();
            client.print("Endereco de IP: ");
            client.println();
            client.print(WiFi.localIP());
            client.println();
            client.print(WiFi.macAddress());
            client.println();
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 2 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 2 off.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        
        if (currentLine.endsWith("GET /H")) {
          // digitalWrite(led1, HIGH);
          // ligar(rele);
          ligar(led2);
          piscar(led1, 2);
        }
        if (currentLine.endsWith("GET /L")) {
          //digitalWrite(led1, LOW);
          // desligar(rele);
          desligar(led2);
          piscar(led4, 2);
        }
        
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
    // piscar(led3, 3);
  }
  

  // btn1 = digitalRead(btn1_pin);   // read the input pin
  // btn2 = digitalRead(btn2_pin);   // read the input pin
  
}