
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//////////////Display///////////////////////
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//////////////Ultrasonic///////////////////////
#define echoPin A1
#define trigPin A2


//////////////LoRa///////////////////////
#include <SPI.h>
#include <LoRa.h>
#define rst 11
#define dio0 9
#define ss 53



//////////////////////////DHT11//////////////////////////////////////////
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h = 0.00;
float t = 0.00;

#include <TinyGPS.h>
float lat,lon;
TinyGPS gps;


int c = 0;

char *KeyList[]={"SD","MX","ZG","PG","TR","LH","NB","WQ","YO","JE","BA"};

int LED = 24;


long duration = 0.00;
float d = 0.00;


void setup_DHT11() {
  dht.begin();
}

//◇─────── EncoderX ──────────◇

String Encoder(String str){
  int str_len = str.length() + 1; 
  char char_array[str_len]; 
  str.toCharArray(char_array, str_len);
  String val;
  for(int n=0; n<str_len; n++){
      String v = String(char_array[n]);
      if (v=="."){
        val+=v;
      }else{
        int g;
        g = v.toInt();
        val+=String(KeyList[g]);
      }
  }
  return val;
  }


//◇───────────────────────◇




//◇─────── OLED Display ────────◇

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup_OLED() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Display failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  ///////////////////////////////////
  display.setTextSize(3);
  display.println("SLIIT");
  display.setTextSize(1);
  display.println("Group Project ID : 2022/289");
  display.print("Boat Unit");
  display.display();
  //delay(2000);
  display.clearDisplay();
  ////////////////////////////////
}

//◇─────── Ultrasonic Sensor ────────◇

void setup_Ultrasonic() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//◇─────── LoRa Setup ────────◇

void setup_LoRa() {
  LoRa.setPins(ss, rst, dio0);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed!");
    //delay(100);
    //while (1);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial1.begin(9600); // connect gps sensor
  setup_LoRa(); 
  setup_OLED();
  setup_Ultrasonic();
  setup_DHT11();
  pinMode(LED, OUTPUT);
  
 
}

void loop() {
  // put your main code here, to run repeatedly:

  gps_loop();
  if (runEvery(2000)) { // repeat every 5000 millis

    Serial.print("Sending packet non-blocking: ");

    // send in async / non-blocking mode
    LoRa.beginPacket();
    String data;
    data = String(lat,6)+String(lon,6)+String(h)+String(t)+String(d);
    LoRa.println(Encoder(data));
    LoRa.print(",");
    //LoRa.print("Latitude: ");
    //LoRa.print(String(lat,6));
    
    //LoRa.print(",");
    
    //Longitude
    //LoRa.print("Longitude: ");
    //LoRa.println(String(lon,6)); 
   // LoRa.print(counter);
    LoRa.endPacket(true); // true = async / non-blocking mode

  }
  
  loop_Ultrasonic();
  delay(100);
  display_data();
  loop_DHT11();
  if (d <1.00){
    digitalWrite(LED, HIGH); 
  }else{
    digitalWrite(LED, LOW); 
  }
  
  
  
}

void display_data(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //display.drawLine(0,0,128, 0, WHITE);
  display.setCursor(0, 0);
  display.println("Distance : " + String(d)+" m");
  display.setCursor(0, 14);
  display.println("Hum : " + String(h)+" %");
  display.setCursor(0, 27);
  display.println("Temp : " + String(t)+" C'");
  display.setCursor(0, 40);
  display.println("Latitude : " + String(lat,6));
  display.setCursor(0, 53);
  display.println("Longitude : " + String(lon,6));
  //display.println(Encoder(String(d)));
  display.display();
}

void loop_Ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  duration = pulseIn(echoPin, HIGH);
  d = ((duration * 0.034 / 2) / 100); //s=(ut/2)
  Serial.print(F("Distance(m) :"));
  Serial.println(d);
}

void loop_DHT11() {
  h = (dht.readHumidity());
  t = (dht.readTemperature());

  if (isnan(h) || isnan(t)) {
    return;
  }

  Serial.print(F("Hum : "));
  Serial.print(h);
  Serial.print(F("% | Temp(°C) : "));
  Serial.println(t);
}


void gps_loop(){
    while(Serial1.available()){ // check for gps data
    if(gps.encode(Serial1.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    
    //Latitude
    Serial.print("Latitude: ");
    Serial.print(lat,6);
    
    Serial.print(",");
    
    //Longitude
    Serial.print("Longitude: ");
    Serial.println(lon,6); 
    
   }
  }
} 

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
