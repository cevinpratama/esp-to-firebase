
// mengimport library dan file yang di butuhkan
#include <Arduino.h> //library arduino wajib
#include <ESP8266WiFi.h> // library untuk menghubungkan esp8266 ke wifi
// #include <WiFi.h>
#include <Firebase_ESP_Client.h> // library untuk menghubungkan esp dengan firestore
#include <addons/TokenHelper.h> // library untuk tambahan dari firebase untuk mengurus token authentikasi
#include "secrets.h" // file untuk menyimpan kunci WiFi, dan konfigurasi firebase


// dikarenakan saya membuat file define WIFI_SSID, WIFI_PASSWORD, API_KEY, DATABASE_URL 
// di file lain yang saya sembunyikan dengan .gitignore
// isinya seperti codingan di bawah ini, kalian bisa menaruh codingannya di bawah ini atau di file lain 

// #define WIFI_SSID "davinnn" Sesuaikan dengan nama wifi saudara"
// #define WIFI_PASSWORD "1paranoia" sesuaikan dengan password wifi saudara"

// #define API_KEY "xxxxx" sesuaikan dengan API_KEY saudara yang terdapat di firebase
// #define DATABASE_URL "xxxxx" Sesuaikan dengan link yang terdapat pada database realtime di firestore

//membuat objek untuk firebase
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void setup() {
  Serial.begin(115200); // untuk melihat di serial monitor
  Serial.println("BOOT OK");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // membuat esp terhubung dengan wifi
  // membuat perulangan untuk memastikan wifi terhubung
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  // jika looping di atas sudah selesai dan terhubung maka akan menampilkan WiFi connected dan ip nya
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  //mengisi object yang sudah kita deklarasikan dengan data kita
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // set atuh, ke mode test
  config.signer.test_mode = true;

  // memulai koneksi ke firebase dan Memberi tahu library Firebase agar otomatis mencoba menyambung ulang WiFi jika koneksi tiba-tiba putus.
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  
  if (Firebase.ready()) { // Mengecek, "Apakah Firebase sudah siap menerima perintah
    if (Firebase.RTDB.setString(&fbdo, "/TEST", "ESP8266_OK")) { // mengirim data ke firebase dengan path /TEST yang berisi ESP8266_OK
      Serial.println("Kirim data BERHASIL!");
    } else {
      Serial.print("Gagal: ");
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("Firebase belum siap...");
  }
  
  // membuat delay 3 detik dan mengirimkannya kembali lagi
  delay(3000);
}
