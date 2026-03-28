// Radar Sysytem code Electrical 6th sem 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo myServo;

int trigPin = 10;
int echoPin = 11;

int redLed = 7;
int greenLed = 6;
int buzzer = 5;

long duration;
int distance;

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(12);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RADAR SYSTEM 6TH EE");
  delay(1000);
}

void loop()
{
  for(int i=15;i<=165;i+=2)
  {
    myServo.write(i);
    delay(7);

    distance = getDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    updateOutput(i);
  }

  for(int i=165;i>15;i-=2)
  {
    myServo.write(i);
    delay(7);

    distance = getDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    updateOutput(i);
  }
}

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  return duration * 0.034 / 2;
}

void updateOutput(int angle)
{
  lcd.setCursor(0,0);
  lcd.print("A:");
  lcd.print(angle);
  lcd.print(" D:");
  lcd.print(distance);
  lcd.print("   ");

  lcd.setCursor(0,1);

  if(distance < 20)
  {
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
    digitalWrite(buzzer,HIGH);

    lcd.print("OBJECT DETECTED ");
  }
  else
  {
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
    digitalWrite(buzzer,LOW);

    lcd.print("SAFE           ");
  }
}
