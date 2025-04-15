#include "WiFi.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "VEGA-WIFI"
#define WIFI_PASSWORD "Vega#@321"

#define API_KEY "AIzaSyAuqH5-eA_ZQrhzaMPx5pb_794S8IKbW-k"
#define DATABASE_URL "https://maritime-communication-system-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

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
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)){

    sendDataPrevMillis = millis();

    //Boat 01 all Data got from LoRa module and Diplay Here


    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    
    // // Write an Float number on the database path test/float
    // if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
    //   Serial.println("PASSED");
    //   Serial.println("PATH: " + fbdo.dataPath());
    //   Serial.println("TYPE: " + fbdo.dataType());
    // }
    // else {
    //   Serial.println("FAILED");
    //   Serial.println("REASON: " + fbdo.errorReason());
    // }

    //Boart Temp
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boart Humidity
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/DHT_Sensor/Humidity", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Ultasonic_Sensor/Distance_01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 02
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Ultasonic_Sensor/Distance_02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Ultasonic_Sensor/Distance_03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Boat_GPS/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Boat_GPS/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //Node 01 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/01/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 01 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/01/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    //Node 02 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/02/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 02 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/02/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

        //Node 03 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/03/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 03 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Node/03/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Error/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Error/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Error Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Error/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Error/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Board Emergnecy Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Emergnecy/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Emergnecy/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Emergnecy Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Emergnecy/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_01/Emergnecy/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Boat 01 all Data got from LoRa module and Diplay Here

     //Boart Temp
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boart Humidity
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/DHT_Sensor/Humidity", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Ultasonic_Sensor/Distance_01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 02
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Ultasonic_Sensor/Distance_02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Ultasonic_Sensor/Distance_03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Boat_GPS/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Boat_GPS/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //Node 01 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/01/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 01 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/01/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    //Node 02 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/02/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 02 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/02/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

        //Node 03 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/03/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 03 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Node/03/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Error/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Error/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Error Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Error/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Error/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Board Emergnecy Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Emergnecy/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Emergnecy/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Emergnecy Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Emergnecy/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_02/Emergnecy/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boat 03 all Data got from LoRa module and Diplay Here


    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boart Humidity
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/DHT_Sensor/Humidity", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Ultasonic_Sensor/Distance_01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 02
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Ultasonic_Sensor/Distance_02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Ultasonic_Sensor/Distance_03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Boat_GPS/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Boat_GPS/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //Node 01 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/01/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 01 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/01/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    //Node 02 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/02/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 02 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/02/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

        //Node 03 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/03/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 03 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Node/03/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Error/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Error/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Error Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Error/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Error/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Board Emergnecy Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Emergnecy/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Emergnecy/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Emergnecy Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Emergnecy/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_03/Emergnecy/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

       //Boat 04 all Data got from LoRa module and Diplay Here

     //Boart Temp
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boart Humidity
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/DHT_Sensor/Humidity", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Ultasonic_Sensor/Distance_01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 02
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Ultasonic_Sensor/Distance_02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Ultasonic_Sensor/Distance_03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Boat_GPS/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Boat_GPS/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //Node 01 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/01/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 01 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/01/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    //Node 02 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/02/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 02 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/02/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

        //Node 03 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/03/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 03 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Node/03/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Error/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Error/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Error Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Error/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Error/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Board Emergnecy Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Emergnecy/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Emergnecy/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Emergnecy Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Emergnecy/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_04/Emergnecy/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    //Boat 05 all Data got from LoRa module and Diplay Here

     //Boart Temp
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/DHT_Sensor/Temp", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     //Boart Humidity
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/DHT_Sensor/Humidity", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Ultasonic_Sensor/Distance_01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 02
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Ultasonic_Sensor/Distance_02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart Distance 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Ultasonic_Sensor/Distance_03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Boat_GPS/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Boart GPS longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Boat_GPS/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //Node 01 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/01/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 01 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/01/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    

    //Node 02 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/02/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 02 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/02/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

        //Node 03 GPS Latitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/03/Latitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Node 03 longitude 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Node/03/Longitude", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Error/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Error/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Error Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Error/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Error Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Error/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

      //Board Emergnecy Message 01
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Emergnecy/01", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 02 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Emergnecy/02", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    //Board Emergnecy Message 03
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Emergnecy/03", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //Board Emergnecy Message 04 
    if (Firebase.RTDB.setInt(&fbdo, "Boat_05/Emergnecy/04", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    count++;
  }

}