#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int Pin1 = 10;
int Pin2 = 11;
int Pin3 = 12;
int Pin4 = 13;
int _step = 0;
boolean dir = true;// false=clockwise, true=counter clockwise
int count = 0;
// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

HX711 load1(3, 2);
HX711 load2(5, 4);
HX711 load3(7, 6);
HX711 load4(9, 8);
void setup() {
  lcd.begin();
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  Serial.begin(9600);
}
long val1 = 0;
float cout1 = 0;
int load10Baht() {
  //cout1 = cout1 +1;
  //val1 = ((cout1-1)/cout1)*val1 + (1/cout1) * load1.read();
  val1 = load1.read();
  float a1 = ((val1 - 8396567) / 964.70f) - 0.5;
  int num1 = a1 / 10.2;
  if (num1 <= 0 ) {
    num1 = 0;
  }
  int baht10 = num1 * 10;
  //Serial.println(baht10);
  //Serial.println(a1);
  return baht10;
}

long val2 = 0;
float cout2 = 0;
int load5Baht() {
  //cout2 = cout2 +1;  //val2 = ((cout2-1)/cout2)*val1 + (1/cout2) * load1.read();
  val2 = load2.read();
  float a2 = ((val2 - 8396567) / 964.70f) + 39;
  int num2 = a2 / 11;
  if (num2 <= 0 ) {
    num2 = 0;
  }
  int baht5 = num2 * 5;
  //Serial.println(baht5);
  return baht5;

}
long val3 = 0;
int load2Baht() {

  val3 = load3.read();
  float a3 = ((val3 - 8296567) / 864.70f) + 110.6;
  int num3 = a3 / 9;
  if (num3 <= 0 ) {
    num3 = 0;
  }
  int baht2 = num3 * 2;
  return baht2;

}
long val4 = 0;
int load1Baht() {

  val4 = load4.read();
  float a4 = ((val4 - 8396567) / 964.70f) + 15;
  int num4 = a4 / 4.2;
  if (num4 <= 0 ) {
    num4 = 0;
  }
  int baht1 = num4 ;
  return baht1;
  //Serial.println(baht1);

}

void StepperMotor() {
  switch (_step) {
    case 0:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
      break;
    case 1:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, HIGH);
      break;
    case 2:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
      break;
    case 3:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
      break;
    case 4:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      break;
    case 5:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      break;
    case 6:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      break;
    case 7:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
      break;
    default:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      break;
  }
  if (dir) {
    _step++;
  } else {
    _step--;
  }
  if (_step > 7) {
    _step = 0;
  }
  if (_step < 0) {
    _step = 7;
  }
  delay(1);
}
void loop() {

  StepperMotor();
  //load2Baht();
  load1Baht();
  int Baht = load10Baht() + load5Baht() + load1Baht() + load2Baht();
  lcd.print("Money:");
  lcd.print(Baht);
  delay(1000);
  lcd.clear();


}
