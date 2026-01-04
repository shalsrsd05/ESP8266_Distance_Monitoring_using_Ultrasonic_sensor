#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// ---------------- Ultrasonic Pins ----------------
#define TRIG_PIN D5   // GPIO14
#define ECHO_PIN D6   // GPIO12

// ---------------- WiFi Credentials ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- MQTT Configuration ----------------
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/ultrasonic";

// ---------------- MQTT Client ----------------
WiFiClient espClient;
PubSubClient client(espClient);

// ---------------- WiFi Setup ----------------
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MQTT Reconnect ----------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266_Ultrasonic_Client")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

// ---------------- Measure Distance ----------------
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  float distance = duration * 0.034 / 2;

  return distance;
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

// ---------------- Loop ----------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float distance = measureDistance();

  // Create JSON payload
  StaticJsonDocument<200> doc;
  doc["distance"] = distance;

  char buffer[128];
  serializeJson(doc, buffer);

  client.publish(mqtt_topic, buffer);

  Serial.print("Published Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000); // Send every 1 second
}
