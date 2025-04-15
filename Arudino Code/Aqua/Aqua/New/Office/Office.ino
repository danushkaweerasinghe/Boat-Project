
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h> 
#include <LoRa.h>
#include <time.h>
#include "base64.hpp"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define FIREBASE_HOST "aqua-safe-167ba-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "6kh9WEU7cJ4V5ReFI4b8rfBun2FTYnM8iy8VgZCx"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define WIFI_SSID "LSW"
#define WIFI_PASSWORD "00000000"

FirebaseData fbdo;


#define ss 15
#define rst 16
#define dio0 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup_display() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  clear_display();
  delay(100);

  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  display.println("SLIIT");
  display.display();
  delay(3000);
  display.clearDisplay();

  init_display2();
  display.println("Aqua Safe");
  display.println("2022-289");
  display.display();
  delay(3000);
  display.clearDisplay();

  init_display1();
  display.print("Starting System...");
  display.display();
  delay(2000);
  display.clearDisplay();

  init_display2();
  // display.println("Name");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void init_display1() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
}
void init_display2() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
}
void clear_display() {
  display.clearDisplay();
}


void setup() {
  // connect to wifi.
  Serial.begin(115200);
  setup_display();
  wifiConnect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6))
  {
    Serial.println(".");
    delay(500);
  }  
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LoRa Initializing OK");
  display.display();
  
  delay(10);

}

void loop() {
  //Firebase.pushString(fbdo,"/Malith", "MTh8MXw3Mi4wMHwyOS4xMHwxMDAzLjk0fDIuMjMA");
  //Firebase.pushString(fbdo,"/Malith", "Test");
  // put your main code here, to run repeatedly:


  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet : '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      LoRaData.trim();
      int rssi = LoRa.packetRssi();
      Serial.print(LoRaData); 
      Serial.println("'");
      Serial.print("RSSI : ");
      Serial.println(rssi);
      
      String ToDecode = "";
      ToDecode = LoRaData;
      ToDecode.replace("x37","w");
      ToDecode.replace("t57","y");
      
      String Decoded = "";
      int data_len = ToDecode.length() + 1;
      char char_arry[data_len];
      ToDecode.toCharArray(char_arry,data_len);
      
      uint8_t raw[BASE64::decodeLength(char_arry)];
      BASE64::decode(char_arry, raw);
      Decoded = String((char*)raw);
      
      Serial.print("Decoded : ");
      Serial.println(Decoded);
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(25, 0);
      display.print(F("Aqua Safe"));
      display.setCursor(0, 18);
      display.print("Data : ");
      display.println(Decoded);
      display.println("");
      display.print("RSSI: ");
      display.println(rssi);
      display.display();

      String Data_ID = "0";
      Data_ID = LoRaData.substring(6,18) + String(rssi);
      Firebase.setString(fbdo,"/Boats/001/Data/"+Data_ID + "/LoRaData" , LoRaData);
      Firebase.setString(fbdo,"/Boats/001/Data/"+Data_ID + "/Decoded" , Decoded);
      Firebase.setInt(fbdo,"/Boats/001/Data/"+Data_ID + "/Rssi" , rssi);
    }

    // print RSSI of packet
    
  }


  
  if(WiFi.status() != WL_CONNECTED)
  {
    wifiConnect();
  }
  delay(1000);
}


void wifiConnect()
{

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("Wifi Connecting to : ");
  display.println( WIFI_SSID );
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Trying to Connect...");
  display.print("\nConnecting..");

  display.display();
  

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
    display.print(".");
    display.display();
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());   
  clear_display();
  display.display();
  display.setCursor(0, 0);
  display.println("Wifi Connected!!");
  display.println(" ");
  display.print("IP : ");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);

}
