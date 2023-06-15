#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <DHT.h>

const char* ssid = "aufarhmn";
const char* password = "infopulangs";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// MPU6050
Adafruit_MPU6050 mpu;

// DHT22
#define DHTPIN 13          // DHT22 data pin
#define DHTTYPE DHT22     // DHT22 sensor type
DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<h2>MPU6050 Accelerometer Data</h2>";
  html += "<p id='accelerometer'></p>";
  html += "<h2>DHT22 Temperature and Humidity Data</h2>";
  html += "<p id='temperature'></p>";
  html += "<p id='humidity'></p>";
  html += "<script>";
  html += "var webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');";
  html += "webSocket.onmessage = function(event) {";
  html += "  var data = JSON.parse(event.data);";
  html += "  if (data.sensor === 'accelerometer') {";
  html += "    document.getElementById('accelerometer').innerHTML = 'X: ' + data.x + ', Y: ' + data.y + ', Z: ' + data.z;";
  html += "  } else if (data.sensor === 'temperature') {";
  html += "    document.getElementById('temperature').innerHTML = 'Temperature: ' + data.temperature.toFixed(2) + '°C';";
  html += "  } else if (data.sensor === 'humidity') {";
  html += "    document.getElementById('humidity').innerHTML = 'Humidity: ' + data.humidity.toFixed(2) + '%';";
  html += "  }";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      Serial.printf("[%u] Connected!\n", num);
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Received data: %s\n", num, payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize MPU6050
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Initialize DHT22
  dht.begin();

  // Initialize web server
  server.on("/", handleRoot);
  server.begin();

  // Initialize WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.println("Server started!");
}

void loop() {
  server.handleClient();
  webSocket.loop();

  // Read MPU6050 accelerometer data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Read DHT22 temperature and humidity data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Create JSON objects for data
  String accelerometerData = String("{\"sensor\":\"accelerometer\",\"x\":") + a.acceleration.x + ",\"y\":" + a.acceleration.y + ",\"z\":" + a.acceleration.z + "}";
  String temperatureData = String("{\"sensor\":\"temperature\",\"temperature\":") + temperature + "}";
  String humidityData = String("{\"sensor\":\"humidity\",\"humidity\":") + humidity + "}";

  // Send data to connected clients
  webSocket.broadcastTXT(accelerometerData);
  webSocket.broadcastTXT(temperatureData);
  webSocket.broadcastTXT(humidityData);

  delay(500); // Adjust delay as per your requirement
}
