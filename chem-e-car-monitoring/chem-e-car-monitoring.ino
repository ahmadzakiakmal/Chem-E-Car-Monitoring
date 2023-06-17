#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "indexPage.h"
#include "aboutPage.h"
#include "settingsPage.h"

// Masukkan SSID dan Password Wi-Fi yang digunakan
const char *ssid = "IOT-ZAKI";
const char *password = "44444444";

// OLED Setup
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Membuat AsyncWebServer object pada port 80
AsyncWebServer server(80);
// Membuat AsyncWebSocket pada path "/ws"
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Koneksi ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print IP Address dari ESP32
  Serial.println(WiFi.localIP());
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("IP Address: ");
  display.println(WiFi.localIP());
  display.display();

  // Start server dan inisiasi web socket
  server.begin();
  server.addHandler(&ws);

  // Route: "/"
  // Method: GET
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
    request->send(200, "text/html", indexPage);
  });
  // Route: "/about"
  // Method: GET
  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", aboutPage);
  });
  // Route: "/settings"
  // Method: GET
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", settingsPage);
  });
}






void loop() {
    ws.cleanupClients();

    // Test random data
    int temp = random(0, 100);

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
