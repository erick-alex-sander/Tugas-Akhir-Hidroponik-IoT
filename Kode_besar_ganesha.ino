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
    client.publish("hidroponik/airtemp/ganesha",airtemp1);
    client.publish("hidroponik/humid/ganesha",humid1);
    client.publish("hidroponik/ph/ganesha1",ph11);
    client.publish("hidroponik/ph/ganesha2",ph12);
    client.publish("hidroponik/ph/ganesha1",ec11);
    client.publish("hidroponik/ph/ganesha2",ec12);
    client.publish("hidroponik/twater/ganesha1",twater11);
    client.publish("hidroponik/twater/ganesha2",twater12);
    client.publish("hidroponik/debit/ganesha1",debit11);
    client.publish("hidroponik/debit/ganesha2",debit12);
    client.publish("hidroponik/level/ganesha11",level111);
    client.publish("hidroponik/level/ganesha12",level112);
    client.publish("hidroponik/level/ganesha13",level113);
    client.publish("hidroponik/level/ganesha14",level114);
    client.publish("hidroponik/level/ganesha21",level121);
    client.publish("hidroponik/level/ganesha22",level122);
    client.publish("hidroponik/level/ganesha23",level123);
    client.publish("hidroponik/level/ganesha24",level124);
    delay(50000);
  }

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
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
