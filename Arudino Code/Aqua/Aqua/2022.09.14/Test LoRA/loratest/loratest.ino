#include <SPI.h>
#include <LoRa.h>

#include <TinyGPS.h>
float lat,lon;
TinyGPS gps;


#define rst 11
#define dio0 9
#define ss 53

String LoRaData;
int counter = 0;
void setup() {
Serial.begin(57600);
Serial.println("LoRa Receiver");
LoRa.setPins(ss, rst, dio0);

if (!LoRa.begin(433E6)) {
  Serial.println("Starting LoRa failed!");
  //delay(500);
  //while (1);
}
//LoRa.onTxDone(onTxDone);
Serial1.begin(9600); // connect gps sensor
}

void loop() {
  if (runEvery(2000)) { // repeat every 5000 millis

    Serial.print("Sending packet non-blocking: ");
    Serial.println(counter);

    // send in async / non-blocking mode
    LoRa.beginPacket();
    LoRa.print("Latitude: ");
    LoRa.print(String(lat,6));
    
    LoRa.print(",");
    
    //Longitude
    LoRa.print("Longitude: ");
    LoRa.println(String(lon,6)); 
   // LoRa.print(counter);
    LoRa.endPacket(true); // true = async / non-blocking mode

    counter++;
  }
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

void onTxDone() {
  Serial.println("TxDone");
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
