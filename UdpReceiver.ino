#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "";
const char* password = "";


WiFiServer server(80);
WiFiUDP udp;


/*
 * Listen on port 2018 for any incoming UDP broadcasts then print whatever is received to the serial console
 */
void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // listen on port 2048 for any incoming UDP packets
  udp.begin(2048);
}

void loop() {
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  int nBytes = udp.parsePacket();
  if(nBytes > 0) {
    udp.read(buffer, nBytes);
    Serial.println(buffer);
  }
  delay(1000);
}
