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
#include <PubSubClient.h>
#include <AiEsp32RotaryEncoder.h>   // Rotary Encoder Library
#include <math.h>                   // Math Library for calculations

// =========================================================================================================
// WiFi SSID and Password
const char *ssid = "IOT-ZAKI";
const char *password = "44444444";

// =========================================================================================================
// MQTT Broker Setup
const char *mqttServer = "192.168.137.1";
const int mqttPort = 1883;
const char *mqttTopic = "ChemECarData";

// =========================================================================================================
// Web Server and Web Socket setup
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// =========================================================================================================
// For MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// =========================================================================================================
// DHT setup
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// =========================================================================================================
// MPU setup
Adafruit_MPU6050 mpu;
float originalHeading = 0.0;

// =========================================================================================================
// Rotary Encoder Setup
#define ROTARY_ENCODER_A_PIN 25         // CLK
#define ROTARY_ENCODER_B_PIN 26         // DT
#define ROTARY_ENCODER_BUTTON_PIN 21    // SW
#define ROTARY_ENCODER_VCC_PIN -1       // VCC

// initialize rotary encoder
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);

// define some constants for the encoder
#define ENCODER_STEPS_PER_REV 30 // number of steps per full revolution
#define ENCODER_WHEEL_DIAMETER 4 // diameter of the wheel attached to the encoder shaft in cm
#define ENCODER_WHEEL_CIRCUMFERENCE (ENCODER_WHEEL_DIAMETER * M_PI) // circumference of the wheel in cm
#define ENCODER_STEP_DISTANCE (ENCODER_WHEEL_CIRCUMFERENCE / ENCODER_STEPS_PER_REV) // distance traveled per step in cm

// define some variables for distance and speed calculation
int encoderPosition = 0; // current position of the encoder
int lastEncoderPosition = 0; // previous position of the encoder
float distance = 0; // total distance traveled by the encoder in cm
float speed = 0; // current speed of the encoder in cm/s
unsigned long lastTime = 0; // previous time of measurement in ms
unsigned long lastEncTime = 0; // previous time the encoder position was measured in ms

// =========================================================================================================
// Setup function
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

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    Serial.println(WiFi.localIP());
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker!");
      Serial.println(WiFi.localIP());
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }

  // DHT
  dht.begin();

  // MPU
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Rotary Encoder Setup
  rotaryEncoder.begin();  // Initialize the rotary encoder and the push button (unused push button)
  rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});  // Update the encoder in the loop, the push button in the ISR
  rotaryEncoder.setBoundaries(0, 10000, true); // set min and max values and enable cycling

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

  if (!client.connected()) {
    while (!client.connected()) {
      Serial.println("Connecting to MQTT broker...");
      if (client.connect("ESP32Client")) {
        Serial.println("Connected to MQTT broker!");
      } else {
        Serial.print("Failed, rc=");
        Serial.print(client.state());
        Serial.println(" Retrying in 5 seconds...");
        delay(5000);
      }
    }
  }

  // =========================================================================================================
  // DHT Data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // =========================================================================================================
  // MPU Data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float wrongHeading = originalHeading + g.gyro.z;

  // =========================================================================================================
  // Rotary Encoder Data
  if(millis() - lastEncTime > 10)
  {
    encoderPosition = rotaryEncoder.encoderChanged(); // get the current position of the encoder
  
    if (encoderPosition != 0) { // if the position has changed
      if(abs(encoderPosition) > 500)
      {
        encoderPosition = 0;
      }
      // int delta = encoderPosition - lastEncoderPosition; // calculate the change in position
      if (encoderPosition != 0) // if the change in position is not zero
      {
        distance += encoderPosition * ENCODER_STEP_DISTANCE; // update the total distance traveled
      }
      unsigned long currentTime = millis(); // get the current time in ms
      unsigned long deltaTime = currentTime - lastTime; // calculate the time elapsed since last measurement
      
      if (deltaTime == 0) { // avoid division by zero error
        deltaTime = 10; // set a very small value instead
      }
      
      speed = (encoderPosition * ENCODER_STEP_DISTANCE) / (deltaTime / 1000.0); // calculate the current speed in cm/s

      lastEncoderPosition = encoderPosition; // update the previous position
      lastTime = currentTime; // update the previous time
    }
  }

  if (isnan(temperature) || isnan(humidity) || isnan(g.gyro.x) || isnan(g.gyro.y) || isnan(g.gyro.z) || isnan(a.acceleration.x) || 
    isnan(a.acceleration.y) || isnan(a.acceleration.z) || isnan(wrongHeading) || isnan(distance) || isnan(speed)) {
    return;
  }

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
  jsonString += ", \"distance\" : ";
  jsonString += distance;
  jsonString += ", \"speed\" : ";
  jsonString += speed;
  jsonString += "}";

  originalHeading = wrongHeading;

  // Sending JSON using websocket
  ws.textAll(jsonString);

  // Sending JSON using MQTT
  client.publish(mqttTopic, jsonString.c_str());

  Serial.println(jsonString);
  delay(1000);
}
