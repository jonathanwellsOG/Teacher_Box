#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "ESP8266-AP";  // AP SSID
const char *password = "12345678"; // AP password

WiFiUDP udp;
IPAddress remoteIP(192, 168, 4, 2);  // IP address of the station ESP8266 (adjust as needed)
int remotePort = 1234;  // Port to send data to

void setup() {
  Serial.begin(115200);
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);

  // Set up WiFi as Access Point
  WiFi.softAP(ssid, password);
  Serial.println("AP Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Show IP address on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println(WiFi.softAPIP());
  display.display();

  delay(1000);
}

void loop() {
 
  if (Serial.available() > 0) {
    String str = Serial.readString();
    str.trim();
    Serial.println(str);
      udp.beginPacket(remoteIP, remotePort);
  udp.write(str.c_str());
  udp.endPacket();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Sent: ");
  display.println(str);
  display.display();
  
}
  String message = "Hello from AP ESP8266!";

  
  // Display sent message on OLED


  delay(1000);  // Send message every 1 second
}
