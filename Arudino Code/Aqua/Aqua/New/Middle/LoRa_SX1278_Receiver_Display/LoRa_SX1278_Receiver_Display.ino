#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//////////////////////////////
#include <LoRa.h>
#include <SPI.h>

#define ss 10
#define rst 9
#define dio0 2
String LoRaData = "";

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  display.println("LoRa Receiver");
  display.display();

  while (!Serial);
  Serial.println("LoRa Receiver");

  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module

  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize)
  {

    Serial.println("Received packet");

    while (LoRa.available())              // read packet
    {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);

    }
    Serial.print("RSSI: ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
    Serial.println("");

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 0);
    display.println("LoRa Receiver");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println(LoRaData);
    display.print("RSSI: ");
    display.println(LoRa.packetRssi());
    display.display();
  }
}
