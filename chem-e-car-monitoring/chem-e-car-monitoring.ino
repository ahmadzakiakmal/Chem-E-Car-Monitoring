#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "indexPage.h"
#include "aboutPage.h"
#include "settingsPage.h"
#include "DHT.h"

// WiFi SSID and Password
const char *ssid = "IOT-ZAKI";
const char *password = "44444444";

// OLED setup
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Web Server and Web Socket setup
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// DHT setup
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Display the IP Address
  Serial.println(WiFi.localIP());
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("IP Address: ");
  display.println(WiFi.localIP());
  display.display();
  // Start server and web socket
  server.begin();
  server.addHandler(&ws);

  // DHT
  dht.begin();

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
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Constructing JSON
    String jsonString = "";
    jsonString += "{\"temperature\" : ";
    jsonString += temperature;
    jsonString += ", \"humidity\" : ";
    jsonString += humidity;
    jsonString += "}";

    // Sending JSON using websocket
    ws.textAll(jsonString);
    Serial.println(jsonString);
    delay(1000);
  }
