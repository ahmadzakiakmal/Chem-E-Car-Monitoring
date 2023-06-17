#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include "indexPage.h"
#include "aboutPage.h"
#include "settingsPage.h"
#include "DHT.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// WiFi SSID and Password
const char *ssid = "IOT-ZAKI";
const char *password = "44444444";

// Web Server and Web Socket setup
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// DHT setup
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// MPU setup
Adafruit_MPU6050 mpu;
float originalHeading = 0.0;

void setup() {
  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Start server and web socket
  server.begin();
  server.addHandler(&ws);

  // DHT
  dht.begin();

  // MPU
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

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

    // DHT Data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    // MPU Data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float wrongHeading = originalHeading + g.gyro.z;

    // Constructing JSON
    String jsonString = "";
    jsonString += "{\"temperature\" : ";
    jsonString += temperature;
    jsonString += ", \"humidity\" : ";
    jsonString += humidity;
    jsonString += ", \"accelerationX\" : ";
    jsonString += a.acceleration.x;
    jsonString += ", \"accelerationY\" : ";
    jsonString += a.acceleration.y;
    jsonString += ", \"accelerationZ\" : ";
    jsonString += a.acceleration.z - 9.8;
    jsonString += ", \"rotationX\" : ";
    jsonString += g.gyro.x;
    jsonString += ", \"rotationY\" : ";
    jsonString += g.gyro.y;
    jsonString += ", \"rotationZ\" : ";
    jsonString += g.gyro.z;
    jsonString += ", \"missAngle\" : ";
    jsonString += wrongHeading;
    jsonString += "}";

    originalHeading = wrongHeading;

    // Sending JSON using websocket
    ws.textAll(jsonString);
    Serial.println(jsonString);
    delay(1000);
  }
