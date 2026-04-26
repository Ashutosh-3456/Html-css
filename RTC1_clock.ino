#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

  // 🔥 Set time (RUN ONLY ONCE, then comment/remove)
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("RTC Time Set!"); 
}

void loop() {
  DateTime now = rtc.now();   

  Serial.print("Date: ");
  Serial.print(now.day()); Serial.print("/");
  Serial.print(now.month()); Serial.print("/");
  Serial.print(now.year());

  Serial.print("  Time: ");
  Serial.print(now.hour()); Serial.print(":");
  Serial.print(now.minute()); Serial.print(":");
  Serial.println(now.second());

  delay(1000);
}