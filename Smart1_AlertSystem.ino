#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID " TMPL3tiLebzlL"
#define BLYNK_TEMPLATE_NAME "Home Security"
#define BLYNK_AUTH_TOKEN "Wo9AhmFsh5OGOGtf44ZjlJ1dWKhfTmUT"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <RTClib.h>

// WiFi
char ssid[] = "vivo 1820";
char pass[] = "12345678";

// Pins
#define PIR_PIN 27
#define BUZZER 26

RTC_DS3231 rtc;

unsigned long lastTrigger = 0;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

  Serial.println("System Ready...");
  delay(30000); // PIR warm-up
}

void loop() {
  Blynk.run();

  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH && millis() - lastTrigger > 2000) {

    lastTrigger = millis();

    DateTime now = rtc.now();

    String timeString = String(now.day()) + "/" +
                        String(now.month()) + "/" +
                        String(now.year()) + " " +
                        String(now.hour()) + ":" +
                        String(now.minute()) + ":" +
                        String(now.second());

    Serial.println("🚨 Motion Detected!");
    Serial.println("Time: " + timeString);

    // 🔊 Buzzer ON
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);

    Serial.println("Sending to Blynk...");

    // 📱 Send notification with time
    Blynk.logEvent("time_update", "Motion at " + timeString);
  }
}