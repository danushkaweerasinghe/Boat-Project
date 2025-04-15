
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

char BaSE64;

#include <SFE_BMP180.h>
SFE_BMP180 pressure;
//#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
char status;
double T = 0.00;
double P = 0.00;


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
  delay(2000);
  display.clearDisplay();
  ////////////////////////////////
}



//////////////////////////DHT11//////////////////////////////////////////
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

#include "Arduino.h"
#include "base64.hpp"

DHT dht(DHTPIN, DHTTYPE);

float h = 0.00;
float t = 0.00;


////////////////////////////LoRa//////////////////////////////////////////
#include <SPI.h>
#include <LoRa.h>


#define ss 10
#define rst 9
#define dio0 2
int c = 0;

//////////////////////////////rain_drop , buzzer////////////////////////////////////////
#define buzzer 7 // pin
#define RainDrop 3
int r = 1;
int b = 1;

///////////////////////////////Ultrasonic///////////////////////////////////////
#define echoPin A1 //pin
#define trigPin A2

long duration = 0.00;
float d = 0.00;
//////////////////////////////////////////////////////////////////////
String dataSet_T = "";
String ECoded = "";


//◇─────── Setup Functions ────────◇

void setup_Rain_Buzzer() {
  pinMode(buzzer, OUTPUT);
  pinMode(RainDrop, INPUT);
}

void setup_DHT11() {
  dht.begin();
}


void setup_BMP180() {
  pressure.begin();
}

void setup_Ultrasonic() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void setup_LoRa() {
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)){
    delay(100);
    while (1);
  }
}


void setup() {
  Serial.begin(9600);
  // setup_OLED();  Not Working Sensors After enable  :(
  setup_Rain_Buzzer();
  setup_DHT11();
  setup_BMP180();
  setup_Ultrasonic();
  setup_LoRa();
}


//◇─────── Loop Area ────────◇

void loop() {
  Serial.print(F("Packet No : "));
  Serial.println(c);

  loop_Rain_Buzzer();
  loop_DHT11();
  loop_bmp();
  loop_Ultrasonic();
  //CollectData();
  loop_LoRa();

  if (c == 100) {
    c = 1;
  }
  c++;
  delay(1000);
}


//◇─────── Loop Functions ────────◇

void loop_Rain_Buzzer() {

  r = digitalRead(RainDrop);
  Serial.print("Rain : ");
  Serial.print(r);
  if (r == 0) { //if Detect Rain value 0 , not rain 1
    digitalWrite(buzzer, HIGH);
    b = 0;
    Serial.println(F(" (Buzzer ON)"));
  }
  else {
    digitalWrite(buzzer, LOW);
    b = 1;
    Serial.println(F(" (Buzzer OFF)"));
  }
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

void loop_bmp()
{
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);


    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print(F("absolute pressure(mbar): "));
          Serial.println(P, 2);
          /////////pressure of 1013.25 millibar = 101325 Pascal//////////
        } else {
          //Serial.println("error retrieving pressure measurement\n");
        }
      } else {
        //Serial.println("error starting pressure measurement\n");
      }
    } else {
      //Serial.println("error retrieving temperature measurement\n");
    }
  } else {
    //Serial.println("error starting temperature measurement\n");
  }

  //delay(1000);  // Pause for 5 seconds.
}

void loop_Ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  d = ((duration * 0.034 / 2) / 100); //s=(ut/2)
  Serial.print(F("Distance(m) :"));
  Serial.println(d);
  //Serial.println(" m");
}

void loop_LoRa() {
  // send packet
  LoRa.beginPacket();
  dataSet_T = "";
  dataSet_T.concat(c);
  dataSet_T.concat("|");
  dataSet_T.concat(r);
  dataSet_T.concat("|");
  dataSet_T.concat(h);
  dataSet_T.concat("|");
  dataSet_T.concat(t);
  dataSet_T.concat("|");
  dataSet_T.concat(P); 
  dataSet_T.concat("|");
  dataSet_T.concat(d);
  Serial.print("Data : ");
  Serial.println(dataSet_T);
  int data_len = dataSet_T.length();
  char char_arry[data_len];
  dataSet_T.toCharArray(char_arry,data_len);
  
  char encoded[BASE64::encodeLength(data_len)];
  BASE64::encode((const unsigned char *)char_arry, data_len, encoded);
  ECoded = String(encoded);
  
  ECoded.replace("w","x37");
  ECoded.replace("y","t57");
  
  ECoded.trim();
  Serial.print("Encoded : ");
  Serial.println(ECoded);
  
  LoRa.println(ECoded);

  LoRa.endPacket();
  Serial.println(F("--------------Data Transmitted--------------"));
  
}
