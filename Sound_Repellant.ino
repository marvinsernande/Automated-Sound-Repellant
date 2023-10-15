#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#include "Countimer.h"

Countimer tDown;

int x, y;
float freq, vol;
int green = 5;
int orange = 6;
int speaker = 9;

int time_s = 0;
int time_m = 0;
int time_h = 0;

int mins_button = 2;
int secs_button = 3;
int startstop_button = 4;
void setup() {
  Serial.begin(9600);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Bee Sound Repellant");
  lcd.setCursor(2, 1);
  lcd.print("Countdown Timer");
  lcd.setCursor(0, 2);
  lcd.print("Set:");
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  digitalWrite(green, 0);
  digitalWrite(orange, 1);
  noTone(9);
  setTimer();
  delay(1000);
  tDown.setCounter(time_h, time_m, time_s, tDown.COUNT_DOWN, tDownComplete);
  // Call print_time2() method every 1s.
  tDown.setInterval(print_time2, 1000);
  startTimer();
}
void setTimer() {
a:
  if (digitalRead(mins_button) == 0) {
    delay(100);
    if (digitalRead(mins_button) == 1) {
      time_m++;
      if (time_m > 59) {
        time_m = 0;
        time_h++;
      }
    }
  }
  if (digitalRead(secs_button) == 0) {
    delay(100);
    if (digitalRead(secs_button) == 0) {
      time_s++;
      if (time_s > 59) {
        time_s = 0;
      }
    }
  }
  if (digitalRead(startstop_button) == 0) {
    return;
  }
  lcd.setCursor(6, 3);
  if (time_h <= 9) {
    lcd.print("0");
  }
  lcd.print(time_h);
  lcd.print(":");
  if (time_m <= 9) {
    lcd.print("0");
  }
  lcd.print(time_m);
  lcd.print(":");
  if (time_s <= 9) {
    lcd.print("0");
  }
  lcd.print(time_s);
  lcd.print("   ");
  goto a;
}
void startTimer() {
  tDown.start();
  lcd.clear();
}

void loop() {
  tDown.run();

  digitalWrite(green, 1);
  digitalWrite(orange, 0);
  x = analogRead(A0);
  y = analogRead(A2);
  //  Serial.println(x);
  //  Serial.print("  ");
  //  Serial.println(y);
  freq = map(x, 0, 1023, 200, 2000); // frequency range
  vol = map(y, 0, 85, 0, 100); // vol range
  tone(speaker, freq);
  if (digitalRead(startstop_button) == 0) {
    tDownComplete();
  }
  lcd.setCursor(0, 0);
  lcd.print("Frequency: ");
  lcd.print(freq, 1);
  lcd.setCursor(2, 1);
  //  lcd.print("Volume: ");
  //  lcd.print(vol, 1);
  lcd.setCursor(0, 2);
  lcd.print("Stop: SW3");
  delay(1);
}
void print_time2()
{
  Serial.print("tDown: ");
  Serial.println(tDown.getCurrentTime());
  lcd.setCursor(6, 3);
  lcd.print(tDown.getCurrentTime());
}
void tDownComplete()
{
  digitalWrite(green, 0);
  digitalWrite(orange, 1);
  time_s = 0;
  time_m = 0;
  time_h = 0;
  lcd.setCursor(6, 3);
  if (time_h <= 9) {
    lcd.print("0");
  }
  lcd.print(time_h);
  lcd.print(":");
  if (time_m <= 9) {
    lcd.print("0");
  }
  lcd.print(time_m);
  lcd.print(":");
  if (time_s <= 9) {
    lcd.print("0");
  }
  lcd.print(time_s);
  lcd.print("   ");
  noTone(9);
  setup();

}
