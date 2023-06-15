#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const char *ssid = "DESKTOP-ZAKI";
const char *password = "44444444";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
WifiClientSecure client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  ws.begin(client, "wss://" + WiFi.localIP())
  ws.onEvent(onEvent);
  server.addHandler(&ws);

  // Route: "/"
  // Method: GET
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Request received");
    String htmlContent = "<body><main><h1>SBM API</h1><h2>Dibuat oleh:</h2><ul><li>Ahmad Zaki Akmal</li><li>Aufa Nasywa Rahman</li><li>Agustinus Angelo Christian Fernando</li><li>Difta Fitrahul Qihaj</li><li>Giga Hidjrika Aura Adkhy</li></ul></main></body>";
    request->send(200, "text/html", htmlContent);
  });
}

void loop() {
  ws.cleanupClients();

  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if(isnan(temp)) {
    temp = 0;
  }

  if(isnan(humidity)) {
    humidity = 0;
  }

  int analogValue = analogRead(32);
  // Rescale to potentiometer's voltage (from 0V to 3.3V):
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  String jsonString = "";
  jsonString += "{";
  jsonString += "\"temperature\" : ";
  jsonString += temp;
  jsonString += ",";
  jsonString += "\"humidity\" : ";
  jsonString += humidity;
  jsonString += ",";
  jsonString += "\"analog\":";
  jsonString += analogValue;
  jsonString += ",";
  jsonString += "\"voltage\":";
  jsonString += voltage;
  jsonString += "}";

  ws.textAll(jsonString);
  Serial.println(jsonString);
  delay(1000);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
  }
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
