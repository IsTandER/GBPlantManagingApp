#include<TM1637Display.h>
#define CLK 2
#define DIO 3
int i=0;
TM1637Display FND(CLK, DIO);
void setup() 
{
}
void loop() 
{ 
  FND.setBrightness(7);
  FND.showNumberDec(i);
  delay(1000);
  i=i+1;
  if(i==10000)
  i=0;

}
