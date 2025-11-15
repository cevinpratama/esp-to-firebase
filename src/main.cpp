#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include "secrets.h"

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void setup() {
  Serial.begin(115200);
  Serial.println("BOOT OK");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  config.signer.test_mode = true;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.setString(&fbdo, "/TEST", "ESP8266_OK")) {
      Serial.println("Kirim data BERHASIL!");
    } else {
      Serial.print("Gagal: ");
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("Firebase belum siap...");
  }

  delay(3000);
}
