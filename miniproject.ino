#define ledPin 6
#define buzz 3
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define sensorPin A0


void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
   pinMode(buzz, OUTPUT);

  digitalWrite(ledPin, LOW);
  lcd.init();
  lcd.backlight();
  lcd.print("HAZARD MONITORING");
  delay(1000);

}


void loop() {
  int sensor = readSensor();
  Serial.print("Analog output: ");
 lcd.clear();

 lcd.setCursor(0,0);
 lcd.print("Senosr reading:");
 lcd.setCursor(0,1);
 lcd.print(sensor);
 delay(1000);
  
  Serial.println(sensor);
  if(sensor>= 170 && sensor<=180 )
  {
    Serial.println("Alert fo smoke");
    lcd.clear();
    lcd.print("SMOKE ALERT");
    delay(1000);
    
    digitalWrite(6, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
  }
  else if(sensor>= 100 && sensor<=110 )
  {
    Serial.println("Alert for Co2");
    lcd.clear();
    lcd.print("CO2 ALERT");
    delay(1000);
    digitalWrite(6, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
  }
   else if(sensor>= 200 && sensor<=230 )
  {
    Serial.println("Alert for LPG");
    lcd.clear();
    lcd.print("LPG ALERT");
    delay(1000);
    digitalWrite(6, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
  }
  else{
  Serial.println("no alert");
  lcd.clear();
    lcd.print("NO ALERT");
    delay(1000);
   digitalWrite(6, LOW);
   digitalWrite(3, LOW);
    delay(500);
  }
  delay(500);

}


//  This function returns the analog data to calling function

int readSensor() {

  unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor

  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data


  if (outputValue > 65)

    analogWrite(ledPin, outputValue); // generate PWM signal


  else

    digitalWrite(ledPin, LOW);

  return outputValue;             // Return analog moisture value

}

