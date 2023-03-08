#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
long hour = 0, minute = 0, second = 10;//second
long countdown_time = (hour * 3600) + (minute * 60) + second;
long pause = 0, pause_start = 0;
const int indication = 10, pause_pin = 5;
int exitloop = 0;
void setup() {
  pinMode(pause_pin, INPUT);
  pinMode(indication, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Pomodoro Timer");
}

void loop() {
  if (digitalRead(pause_pin) == LOW && exitloop == 0) { // Pause
    pause_start = (millis() / 1000) - pause;
    while (1) {
      pause = (millis() / 1000);
      if (digitalRead(pause_pin) == LOW && exitloop == 1) { // Resume
        pause = pause - pause_start;
        exitloop = 0;
        lcd.setCursor(0, 1);
        lcd.print(" ");
        break;
      }
      lcd.setCursor(0, 1);
      lcd.print("!");// Indicate pause
      if (digitalRead(pause_pin) == HIGH) {
        exitloop = 1;
      }
      delay(100);
    }
  }
  long countdowntime_seconds = countdown_time + pause - (millis() / 1000);
  if (countdowntime_seconds >= 0) {
    long countdown_hour = countdowntime_seconds / 3600;
    long countdown_minute = ((countdowntime_seconds / 60) % 60);
    long counddown_sec = countdowntime_seconds % 60;
    lcd.setCursor(4, 1);
    if (countdown_hour < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_hour);
    lcd.print(":");
    if (countdown_minute < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_minute);
    lcd.print(":");
    if (counddown_sec < 10) {
      lcd.print("0");
    }
    lcd.print(counddown_sec);
    if (countdowntime_seconds == 0) {
      digitalWrite(indication, HIGH);
    }
  }
  delay(500);
}