#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int TRIG_PIN1 = 6;
const int ECHO_PIN1 = 7;
const int TRIG_PIN2 = 8;
const int ECHO_PIN2 = 9;
const int LED_PINVerde  = 3;
const int LED_PINRosu = 4;
const int LED_PINAlbastru = 2;
const int BUZZER_PIN = 10;
const int BUTTON_PIN = 13;
const int DISTANCE_THRESHOLD = 50;
const int DISTANCE = 30;
float duration_us, distance_cm;
float duration, distance;
bool asezat = false;
int counter = 0;
int snoozeTime = -10;

void setup() {
  Serial.begin (9600);

  lcd.begin();
  lcd.backlight();


  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);

  pinMode(LED_PINVerde, OUTPUT);
  pinMode(LED_PINRosu, OUTPUT);
  pinMode(LED_PINAlbastru, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT);
}



void loop() {
  digitalWrite(TRIG_PIN1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN1, LOW);
    duration_us = pulseIn(ECHO_PIN1, HIGH);
    distance_cm = 0.017 * duration_us;
    if(distance_cm > DISTANCE_THRESHOLD){
    digitalWrite(LED_PINVerde, HIGH);
    digitalWrite(LED_PINRosu,LOW);
    digitalWrite(LED_PINAlbastru,LOW);
    }
    else{ if(distance_cm>DISTANCE){
          digitalWrite(LED_PINVerde, LOW);
          digitalWrite(LED_PINAlbastru,HIGH);
          digitalWrite(LED_PINRosu,LOW);
    }

    else {
    digitalWrite(LED_PINVerde,LOW);
    digitalWrite(LED_PINAlbastru,LOW);
    digitalWrite(LED_PINRosu,HIGH);
    }

    }
    Serial.print("distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    //delay(500);

  //SCAUN
  
  lcd.clear();
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration = pulseIn(ECHO_PIN2, HIGH);
  distance = 0.017 * duration;



  if (distance < 15) {
    if (asezat) {
      counter++;
      if (counter > 5) {
        int but = digitalRead(BUTTON_PIN);

        if (but == 1) {
          snoozeTime = counter;
        }

        if (counter - snoozeTime > 10) {
          digitalWrite(BUZZER_PIN, HIGH);
          delay(500);
          digitalWrite(BUZZER_PIN, LOW);
          //delay(250);
        } else {
          delay(500);
        }


        lcd.setCursor(2, 0);
        lcd.print("TREBUIE SA");
        lcd.setCursor(2, 1);
        lcd.print("VA RIDICATI");
        //          lcd.print(counter);
        //          lcd.print(" ");
        //          lcd.print(snoozeTime);

        delay(500);
      } else {
        snoozeTime = -10;
        lcd.print(counter);
        delay(1000);
      }
    } else {
      asezat = true;
      counter = 0;
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    asezat = false;
    lcd.setCursor(3, 0);
    lcd.print("VA PUTETI");
    lcd.setCursor(5, 1);
    lcd.print("ASEZA");
    delay(500);
  }
}
