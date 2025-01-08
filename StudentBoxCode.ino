#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "ESP8266-AP";  // SSID of the Access Point (AP)
const char *password = "12345678"; // Password for AP

WiFiUDP udp;
int localPort = 1234;  // Port to listen for incoming messages

void setup() {
  Serial.begin(115200);
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C )) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Show IP address on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();

  // Begin listening on UDP port
  udp.begin(localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null terminate the string
    }
    
    // Display the received message on the OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Received: ");
    display.println(incomingPacket);
    display.display();
  }

  delay(100);  // Small delay to not overload the loop
}
