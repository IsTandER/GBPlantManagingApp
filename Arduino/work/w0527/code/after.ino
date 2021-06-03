#include <Wire.h>                     // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 2004 I2C용 라이브러리
#include <Servo.h>
#define buz 7
LiquidCrystal_I2C lcd(0x27, 16, 2);   //  0x3F or 0x27를 선택하여 주세요. 작동이 되지 않는 경우 0x27로 바꾸어주세요. 확인결과 0x3f가 작동하지 않을 수 있습니다.
//고유주소가 LCD마다 다르기 때문입니다.
unsigned long distance = 0;


#define trigPin1 8  // 초음파 발신핀 define은 쉽게말하면, 숫자의 이름을 정의해주는것. 
#define echoPin1 9  // 초음파 수신핀

//변수를 설정합니다.
long duration1, distance1;

void setup()
{
  pinMode(trigPin1, OUTPUT);  // trig를 출력 모드로 설정
  pinMode(echoPin1, INPUT);   // echo를 입력모드로 설정
  pinMode(buz, OUTPUT);  // 피에조 부저 출력 설정

  Serial.begin(9600);        //시리얼 프린트 시작
  lcd.init();                // LCD 초기화
  lcd.backlight();           // 백라이트 켜기

}

void loop()
{
  //초음파 센서를 한번 초기화 하는 과정입니다. 마치 껏다 켯다를 하면서 거리를 초기화합니다.
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  Serial.print("거리: ");
  Serial.print(distance1); // 거리를 시리얼 모니터에 출력
  Serial.println("cm");
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Distance Check");
  lcd.setCursor(5, 1);
  lcd.print(distance1); lcd.print(" cm");
  delay(200);
  lcd.setCursor(1, 3);

  if (distance1 > 60 && distance1 < 100)
  {
    tone(buz, 2093, 20);
    delay(150);
  }

  else if (distance1 <= 60 && distance1 > 30)
  {
    tone(buz, 2093, 30);
    delay(100);
  }

  else if (distance1 <= 30 && distance1 > 10)
  {
    tone(buz, 2093, 40);
    delay(50);
  }

  else if (distance1 <= 50)
  {
    tone(buz, 2093, 50);
    delay(1);
  }


}
