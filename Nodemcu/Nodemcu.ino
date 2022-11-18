#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<WiFiManager.h>

#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
/*Ağ adınızı ve Şifrenizi Giriniz*/
const char* ssid = "Network-id";  // Ağ adınızı girin
const char* password = "Network-Password";  //Ağ şifrenizi girin

ESP8266WebServer server(80); //80 portunu kullanarak bir webserver nesnesi oluşturduk

uint8_t LED1pin = D7;
bool LED1status = LOW;

uint8_t LED2pin = D6;
bool LED2status = LOW;

uint8_t LED3pin = D1;
bool LED3status = LOW;

uint8_t LED4pin = D2;
bool LED4status = LOW;

HTTPClient http;
WiFiClient client;
String  httpurl;

void setup() {
  Serial.begin(115200);
  
  // Config Static IP
  IPAddress local_IP(192, 168, 1, 39);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.mode(WIFI_STA);

  
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.....");
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  
  delay(100);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);


  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/ledalloff", handle_ledalloff);
  server.on("/ledallon", handle_ledallon);
  server.on("/ledsignaloff", handle_ledsignaloff);
  server.on("/ledsignalon", handle_ledsignalon);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Sunucusu Başlatıldı");
}
void loop() {
  
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
  
  if(LED3status)
  {digitalWrite(LED3pin, HIGH);}
  else
  {digitalWrite(LED3pin, LOW);}
  
  if(LED4status)
  {digitalWrite(LED4pin, HIGH);}
  else
  {digitalWrite(LED4pin, LOW);}
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  LED4status = LOW;
  Serial.println("GPIO7 Durumu: OFF | GPIO6 Durumu: OFF | GPIO1 Durumu: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Durumu: ON");
  server.send(200, "text/html", SendHTML(true,LED1status)); 
  http.GET();
  http.end();

}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Durumu: OFF");
  server.send(200, "text/html", SendHTML(false,LED1status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Durumu: ON");
  server.send(200, "text/html", SendHTML(LED2status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Durumu: OFF");
  server.send(200, "text/html", SendHTML(LED2status,false)); 
}

void handle_led3on() {
  LED3status = HIGH;
  Serial.println("GPIO4 Durumu: ON");
  server.send(200, "text/html", SendHTML(LED3status,true)); 
}

void handle_led3off() {
  LED3status = LOW;
  Serial.println("GPIO4 Durumu: OFF");
  server.send(200, "text/html", SendHTML(LED3status,false)); 
}

void handle_ledsignalon() {
  LED4status = HIGH;
  Serial.println("GPIO4 Durumu: ON");
  server.send(200, "text/html", SendHTML(LED4status,true)); 
}

void handle_ledsignaloff() {
  LED4status = LOW;
  Serial.println("GPIO4 Durumu: OFF");
  server.send(200, "text/html", SendHTML(LED4status,false)); 
}


void handle_ledallon() {
  LED2status = HIGH;
  LED1status = HIGH;
  LED3status = HIGH;
  Serial.println("All GPIO Durumu: ON");
  server.send(200, "text/html", SendHTML(LED3status,true)); 
  server.send(200, "text/html", SendHTML(LED2status,true)); 
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_ledalloff() {
  LED2status = LOW;
  LED1status = LOW;
  LED3status = LOW;
  Serial.println("All GPIO Durumu: OFF");
  server.send(200, "text/html", SendHTML(LED3status,false)); 
  server.send(200, "text/html", SendHTML(LED2status,false)); 
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Sayfa Bulunamadı");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  
  return ptr;
}
