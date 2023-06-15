#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Masukkan SSID dan Password Wi-Fi yang digunakan
const char *ssid = "DESKTOP-ZAKI";
const char *password = "88888888";

// Membuat AsyncWebServer object pada port 80
AsyncWebServer server(80);
// Membuat AsyncWebSocket pada path "/ws"
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);

  // Koneksi ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print IP Address dari ESP32
  Serial.println(WiFi.localIP());

  // Start server dan inisiasi web socket
  server.begin();
  initWebSocket();

  // Route: "/"
  // Method: GET
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Request received");
    String htmlContent = "<h1>Test</h1>";
    request->send(200, "text/html", htmlContent);
  });
}

void loop() {
  ws.cleanupClients();

  // Test random data
  int temp = random(0,100);

  // Constructing JSON
  String jsonString = "";
  jsonString += "{";
  jsonString += "\"temperature\" : ";
  jsonString += temp;
  jsonString += "}";

  // Sending JSON using websocket
  ws.textAll(jsonString);
  Serial.println(jsonString);
  delay(500);
}

// Websocket setup
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// Check websocket connection from client side
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