#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN PB0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
  delay(1000);
}

void loop() {
  delay(2000);                        // DHT22 ki 2 sec gap kavali
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.clear();
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor error");
    lcd.print("Sensor error");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t, 1);
  Serial.print(" C  Humidity: ");
  Serial.print(h, 1);
  Serial.println(" %");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(h, 1);
  lcd.print(" %");
}