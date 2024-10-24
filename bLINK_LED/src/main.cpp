#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>

WiFiClient espClient;
PubSubClient client(espClient);
const char *mqtt_broker = "broker.mqttdashboard.com";
const char *topic_pub = "Esp32/Mqtt";
const char *topic_sub = "Mqtt/Esp32";
const char *mqtt_username = "DucAnh";
const char *mqtt_password = "0309";
const int mqtt_port = 1883;

const char *ssid = "ESP32";  // Replace with your WiFi SSID
const char *password = "12345678"; // Replace with your WiFi password

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Message arrived: " + String(topic));
  Serial.println("Payload: ");
  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  DynamicJsonDocument doc(256);  // Điều chỉnh kích thước tùy theo nhu cầu
  DeserializationError error = deserializeJson(doc, payload);
  
  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Kiểm tra giá trị "Value_led" trong chuỗi JSON
  int valueLed = doc["Value_led"].as<int>();
  Serial.println("Value: " + String(valueLed));
  if (valueLed == 1)
  {
    digitalWrite(26, HIGH); // Bật đèn
  }
  else if (valueLed == 0)
  {
    digitalWrite(26, LOW); // Tắt đèn
  }
}

void MQTT_Connect()
{
  // connecting to an MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Public emqx mqtt broker connected");
      client.subscribe(topic_sub);
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup()
{
  Serial.begin(9600); // Initialize serial communication
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.localIP());
  MQTT_Connect();
  pinMode(26,OUTPUT);
  digitalWrite(26,HIGH);
}

void loop()
{
  client.loop();
  client.subscribe(topic_sub);
}
