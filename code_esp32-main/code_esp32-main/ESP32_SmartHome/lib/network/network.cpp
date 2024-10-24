#include <network.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>

char sendData[1000] = "Welcome to Embedded Aiot Lab!";

const char *WIFI_SSID = "ThaiSalem";
const char *WIFI_PASSWORD = "motdenchin";

String messageTemp;

typedef enum
{
    NONE,
    NETWORK_SEARCHING,
    NETWORK_CONNECTED_POPUP,
    NETWORK_CONNECTED,
    NETWORK_CONNECT_FAILED
} Network_Status_t;
Network_Status_t networkStatus = NONE;
static int foundNetworks = 0;
unsigned long networkTimeout = 20 * 1000;

void Wifi_Setup()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        vTaskDelay(100);
    }
    Serial.println("AP IP address: ");
    Serial.println(WiFi.localIP());
}

void WIFI_Connect()
{

    unsigned long startingTime = millis();
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(WIFI_PASSWORD, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED && (millis() - startingTime) < networkTimeout)
    {
        Serial.print(".");
        delay(150);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        networkStatus = NETWORK_CONNECTED_POPUP;
        Serial.println("Wifi Connected");
        Serial.println("IP: " + String(WiFi.localIP()));
    }
    else
    {
        networkStatus = NETWORK_CONNECT_FAILED;
        Serial.println("Wifi not Connect");
    }
}
