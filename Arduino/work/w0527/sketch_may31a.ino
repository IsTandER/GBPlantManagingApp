#include <LiquidCrystal_I2C.h>


#define DELAY 1000
LiquidCrystal_I2C lcd(0x3f,16,2);
void setup() {
 lcd.backlight();
 lcd.print("Start");
 delay(DELAY);

 lcd.setCursor(0,0);
 lcd.print("1234567890");
 delay(DELAY);

 lcd.cursor();

 lcd.clear();
 lcd.print("abc");
 delay(DELAY);
 lcd.noDisplay();
 delay(DELAY);
 lcd.display();
 delay(DELAY);

 lcd.print("ABCEFG");
 delay(DELAY);

 lcd.blink();
 delay(5000);
 lcd.noBlink();
 delay(5000);
 
}

void loop() {
  
}
