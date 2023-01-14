#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "ARRIS-1FA2"
#define WIFI_PASS "31415926535"
#define UDP_PORT 4210
#define NODE_RED_IP "192.168.0.4"
#define outPin 0

WiFiUDP UDP;
char packet[255];
bool led = false;

uint16_t ipAddress = 192168000007;
uint16_t port = 4210;

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(9600);
  Serial.println();

  WiFi.begin(WIFI_SSID,WIFI_PASS);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  UDP.begin(UDP_PORT);
  Serial.print("Listening to UDP port ");
  Serial.println(UDP_PORT);
  pinMode(outPin, OUTPUT);
}

void loop() {
  // unsigned long currentMillis = millis();
  // if (currentMillis- previousMillis >= interval) {
  //   UDP.beginPacket("192.168.0.4",1234);
  //   UDP.write("Hello from One!");
  //   UDP.endPacket();
  //   previousMillis = currentMillis;
  // }
  

  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0) {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);

    if (strcmp(packet, "test") == 0){
      if (led) {
        digitalWrite(outPin,LOW);
        led = false;
      } else {
        digitalWrite(outPin, HIGH);
        led = true;
      }
    }
    // UDP.beginPacket(UDP.remoteIP(),UDP.remotePort());
    // UDP.write(stringCount);
    // UDP.endPacket();
  }
}
