#include<LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int TrigPin = 7;
const int EchoPin = 6;

int Buzzer_Pin = 5;
int Tones_Number;
int distance;



void setup()
{
 Serial.begin(9600);
 pinMode(TrigPin, OUTPUT);
 pinMode(EchoPin, INPUT);

 lcd.init();

 lcd.backlight();
}

void loop()
{
   digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  int distance=pulseIn(EchoPin, HIGH);
  distance = distance/20;
  Serial.println(distance);

  long duration=pulseIn(EchoPin, HIGH);
  long diatance = duration*0.034/2;



  if(distance<100&&distance>=1){
  
  Serial.print(distance/10);
  Serial.println("cm");

  lcd.setCursor(0,0);
  lcd.print("Distance_Alert");
  lcd.setCursor(0,1);
  lcd.print("Distance :");
  lcd.setCursor(9,1);
  lcd.print(distance);
  lcd.setCursor(14,1);
  lcd.print("cm");
  delay(500);
  }
  distance = 0;
  duration = 0;

//  if(distance < 30){
//    tone(Buzzer_Pin, Tones[01]);
//    delay(100);
//    noTone(Buzzer_Pin);
//    delay(200);
//  }
//  else delay(200);
}
