#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <ESP32Servo.h>
#define WIFI_SSID "UIU-STUDENT"
#define WIFI_PASSWORD "12345678"

#define API_KEY "YlL6fkL2aYHnm7FByVpOOf6FxkgE7AMy7I3FR17T"
#define DATABASE_URL "microlab-softrix-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

//Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


Servo panServo;
String main="";

int a, b, x, y;
int irSensor1, irSensor2, irSensor3, fireSensor;


void setup()
{

  Serial.begin(9600);

  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print(".");
    delay(300);
  }
  //Serial.println();
 // Serial.print("Connected with IP: ");
  //Serial.println(WiFi.localIP());
  //Serial.println();

  //Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;
  Firebase.begin(DATABASE_URL, API_KEY);

  Firebase.setDoubleDigits(5);

  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  
  pinMode(12, INPUT); //IR SENSOR 
  pinMode(13, INPUT); //IR SENSOR2 
  pinMode(2, INPUT); //IR SENSOR3
  pinMode(16, INPUT); //Flame Sensor
  panServo.attach(14);
  panServo.write(0);
}

void loop()
{
  
  if (Firebase.ready()) 
  {
    //digitalWrite(4, HIGH);
    //Firebase.setInt(fbdo, "/motor/status", 1);
    //panServo.write(90);
    //Serial.printf("Get int a--  %s\n",  ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Firebase.getInt(fbdo, "/motor/status");
     a=fbdo.to<int>();
    if(a == 1){
      digitalWrite(4, HIGH);
      digitalWrite(15, HIGH);
      //Serial.write("Starting Car Wash");
    }else if(a==0){
      digitalWrite(4, LOW);
      digitalWrite(15, LOW);
      //Serial.write("Stoping Car Washing");
    }
    
    irSensor1 = digitalRead(12);
    if(irSensor1 == 1){
      Firebase.setInt(fbdo, "/irsensor/sensor1", 0);
    }else if(irSensor1 == 0){
      Firebase.setInt(fbdo, "/irsensor/sensor1", 1);      
    }
    
    irSensor2 = digitalRead(13);
     if(irSensor2 == 1){
      Firebase.setInt(fbdo, "/irsensor/sensor2", 0);
    }else if(irSensor2 == 0){
      Firebase.setInt(fbdo, "/irsensor/sensor2", 1);
    }
    irSensor3 = digitalRead(2);
     if(irSensor3 == 1){
      Firebase.setInt(fbdo, "/irsensor/sensor3", 0);
    }else if(irSensor3 == 0){
      Firebase.setInt(fbdo, "/irsensor/sensor3", 1);
    }

    // fireSensor = digitalRead(16);
    // if(fireSensor == 1){
    //   Firebase.setInt(fbdo, "/fireSensor/status", 1);
    //   Serial.write("!!!FIRE!!!");
    // }else if(fireSensor == 0){
    //   Firebase.setInt(fbdo, "/fireSensor/status", 0);
    // }    

     //Serial.printf("Get int a--  %s\n", Firebase.getInt(fbdo, "/gates/status") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
     Firebase.getInt(fbdo, "/gates/status");
     b=fbdo.to<int>();
     if(b == 1){
       Serial.write("Opening Gate");
       panServo.write(90);
       
       delay(5000);
       panServo.write(0);
       Serial.write("Closing Gate");
       Firebase.setInt(fbdo, "/gates/status", 0);
      
    }
  

  delay(2000);
  int available = irSensor1+ irSensor2 + irSensor3; 
  if(available == 0){
    Serial.write("Parking Full");
  }else{
    Serial.write("Parking Available");
  }
  
  }
}