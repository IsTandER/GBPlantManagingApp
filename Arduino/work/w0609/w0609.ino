int LED = 5;

void setup() {
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
}

void loop() {
  int soil = analogRead(A1);
  Serial.println(soil);
  if(soil < 500)
    digitalWrite(LED, HIGH);
  else
  {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED ,LOW);
  }
  delay(500);
}
