int x, y;
float z;
void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  x = analogRead(A0);
  y = analogRead(A2);
  //  Serial.println(x);
  //  Serial.print("  ");
  Serial.println(y);
  // z = map(x, 0, 1023, 27.5, 4186);
  z = map(x, 0, 1023, 200, 4000);
  tone(9, z);
  delay(1);
  //  noTone(9);
  //  delay(10);
}
