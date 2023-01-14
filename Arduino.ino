#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial mySerial(2, 3);
Servo servo1;
void setup()
{
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(5000);
  lcd.init();
  lcd.backlight();
 }
 
void loop(){
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan QR to Book");
  delay(2000);
  lcd.clear();
  lcd.print(mySerial.readString());
  delay(1000);
  lcd.clear();
  if(digitalRead(8)==LOW){
    digitalWrite(9, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("!!!!FIRE!!!!");
    delay(2000);
    lcd.clear();
    digitalWrite(9, LOW);
  }
}