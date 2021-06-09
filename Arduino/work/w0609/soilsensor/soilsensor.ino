#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int Sensor_pin = A1;    // 토양수분센서 핀을 A1으로 설정
int LED_R = 5;          // 빨간색 LED 핀을 3번핀으로 설정
int LED_G = 4;          // 초록색 LED 핀을 4번핀으로 설정

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();        // 백라이트 ON

  pinMode(LED_R, OUTPUT); // 빨간색 LED핀을 출력으로 설정
  pinMode(LED_G, OUTPUT); // 초록색 LED핀을 출력으로 설정
}

void loop()
{
  Serial.println(analogRead(Sensor_pin));    // 센서값을 시리얼모니터로 전송
  delay(100);                                 // 0.1초 간격으로 센서값 출력

  if (analogRead(Sensor_pin) > 400) {         // 토양에 수분이 부족하면
    lcd.clear();
    digitalWrite(LED_R, HIGH);                // 빨간색 LED ON
    digitalWrite(LED_G, LOW);
    lcd.setCursor(1, 0);
    lcd.print("Water, please");               // 'Water,please' 문구 출력
  }
  else {                                      // 토양에 수분이 충분하면
    lcd.clear();
    digitalWrite(LED_G, HIGH);                // 초록색 LED ON
    digitalWrite(LED_R, LOW);
    lcd.setCursor(5, 0);
    lcd.print("Enough");                      // 'Enough' 문구 출력
  }
}
