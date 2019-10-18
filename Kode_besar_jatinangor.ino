#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>

char ssid[]="CITA-ITB";   
char pass[]="wific1t4";
int status=WL_IDLE_STATUS;

// Initialize the Ethernet client object
WiFiEspClient espClient;

PubSubClient client(espClient);


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial1.begin(115200);
WiFi.init(&Serial1(;

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
    while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");

  client.setServer("167.205.27.112", 1883);
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
    if (client.connected()) {
    client.publish("hidroponik/airtemp/jatinangor",airtemp2);
    client.publish("hidroponik/humid/jatinangor",humid2);
    client.publish("hidroponik/ph/jatinangor1",ph21);
    client.publish("hidroponik/ph/jatinangor2",ph22);
    client.publish("hidroponik/ph/jatinangor1",ec21);
    client.publish("hidroponik/ph/jatinangor2",ec22);
    client.publish("hidroponik/twater/jatinangor1",twater21);
    client.publish("hidroponik/twater/jatinangor2",twater22);
    client.publish("hidroponik/debit/jatinangor1",debit21);
    client.publish("hidroponik/debit/jatinangor2",debit22);
    client.publish("hidroponik/level/jatinangor11",level211);
    client.publish("hidroponik/level/jatinangor12",level212);
    client.publish("hidroponik/level/jatinangor13",level213);
    client.publish("hidroponik/level/jatinangor14",level214);
    client.publish("hidroponik/level/jatinangor21",level221);
    client.publish("hidroponik/level/jatinangor22",level222);
    client.publish("hidroponik/level/jatinangor23",level223);
    client.publish("hidroponik/level/jatinangor24",level224);
    delay(50000);
  }

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Jatinangor")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  
  client.loop();
}
