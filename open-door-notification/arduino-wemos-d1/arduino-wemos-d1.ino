#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WEB_URL "http://192.168.0.105" // Посилання на локальний веб сервер
#define WIFI_SSID "WIFI_SSID" // WiFi логін
#define WIFI_PASSWORD "WIFI_PASSWORD" // WiFi пароль

int switchStateRead = D6;
bool doorState = true;

void setup() {
  Serial.begin(9600);
  pinMode(switchStateRead, INPUT);

  // connect wifi
  connectWiFi(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  int switchState = digitalRead(switchStateRead);

  if(!switchState && !doorState) {
    doorState = true;

    sendMessage(WEB_URL, "{\"state\": true}");
  } else if(switchState && doorState) {
    doorState = false;

    sendMessage(WEB_URL, "{\"state\": false}");
  }
}

/**
 * Функція під'єднання до WiFi 
 */
void connectWifi(char ssid[], char password[]) {
  WiFi.begin(ssid, password);
  delay(2000);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print("\nWiFi connected. IP:");
    Serial.print(WiFi.localIP());
  }
}

/**
 * Функція відправлення http POST запиту
 */
void sendMessage(String url, String message) {
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    http.POST(message);
    http.end();
  }
}

