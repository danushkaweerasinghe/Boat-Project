#include "WiFi.h"
#include<Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <LoRa.h>

#define WIFI_SSID "VEGA-WIFI"
#define WIFI_PASSWORD "Vega#@321"

#define API_KEY "AIzaSyAuqH5-eA_ZQrhzaMPx5pb_794S8IKbW-k"
#define DATABASE_URL "https://maritime-communication-system-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

#define ss 15
#define rst 16
#define dio0 2

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6))
  {
    Serial.println(".");
    delay(500);
  }  
  LoRa.setSyncWord(0xA5);




}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;
    
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
      

      // Decoded = String((char*)raw);
      
      Serial.print("Decoded : ");
      Serial.println(Decoded);
      
     

      String Data_ID = "0";
      Data_ID = LoRaData.substring(6,18) + String(rssi);
      Firebase.setString(fbdo,"/Boats/001/Data/"+Data_ID + "/LoRaData" , LoRaData);
      Firebase.setString(fbdo,"/Boats/001/Data/"+Data_ID + "/Decoded" , Decoded);
      Firebase.setInt(fbdo,"/Boats/001/Data/"+Data_ID + "/Rssi" , rssi);
    }

    // print RSSI of packet
    
  }

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}