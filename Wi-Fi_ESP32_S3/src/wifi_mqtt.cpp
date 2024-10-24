#include <wifi_mqtt.h>

WiFiClient espClient;
PubSubClient client(espClient);
const char *mqtt_broker = "broker.mqttdashboard.com";
const char *topic_pub = "Esp32/Mqtt";
const char *topic_sub = "mqtt/esp32";
const char *mqtt_username = "DucAnh";
const char *mqtt_password = "0309";
const int mqtt_port = 1883;

const char *ssid = "SepCung";        // Replace with your WiFi SSID
const char *password = "hongcopass"; // Replace with your WiFi password

void WiFi_setup()
{
    Serial.begin(115200);
    Serial.println("Connecting to Wi-Fi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message arrived: " + String(topic));
    Serial.println("Payload: ");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
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

void run_mqtt()
{
    client.loop();
    client.publish(topic_pub, "Hello from ESP32");
    client.subscribe(topic_sub);
}