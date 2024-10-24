#ifndef _MQTT_H_
#define _MQTT_H_

#include <ArduinoJson.h>
#include <Arduino.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>

extern WiFiClient espClient;
extern PubSubClient client;
extern const char *mqtt_broker;
extern const char *topic_pub;
extern const char *topic_sub;
extern const char *mqtt_username;
extern const char *mqtt_password;
extern const int mqtt_port;

// externconst char *ssid;     // Replace with your WiFi SSID
// extern const char *password; // Replace with your WiFi password

void WiFi_setup();
void callback(char *topic, byte *payload, unsigned int length);
void MQTT_Connect();
void run_mqtt();

#endif