int red = 12;
int blue = 5;

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  int soil = analogRead(A1);
  Serial.println(soil);
  if(soil < 500)
    digitalWrite(blue, HIGH);
  else
  {
    digitalWrite(blue, HIGH);
    delay(200);
    digitalWrite(blue ,LOW);
  }
  delay(500);
}
