#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)

//////////////////////////////
#include <LoRa.h>
#include <SPI.h>

#define ss 10
#define rst 9
#define dio0 2
String LoRaData = "";

void setup() {
  Serial.begin(9600);


  //while (!Serial);
  Serial.println("LoRa Receiver");

  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module

  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  //LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  delay(500);
  //Serial.print("Working");
  Serial.print(LoRa.readString());
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

  }
}
