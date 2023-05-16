// Library yang dibutuhkan
#include "DHT.h"
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

// Mendefinisikan pin dan tipe sensor DHT
#define DHTPIN D6
#define DHTTYPE DHT11
DHT dht11(DHTPIN, DHTTYPE);
int led = D7;

// Isikan sesuai pada Firebase
#define FIREBASE_HOST "https://monitoring-c8ac0-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "8X1kmytIQesZRC9XZepDnyMPrtVod6vpoj0gXh0f"

//Nama Wifi
#define WIFI_SSID "KHASAN JAYA 123"
#define WIFI_PASSWORD "10072010,afisya13" 

// mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
 
  dht11.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); //nilai awal relay akan off
  // Koneksi ke Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}



void loop(){
  // Sensor DHT11 membaca suhu dan kelembaban
  float t = dht11.readTemperature();
  float h = dht11.readHumidity();

  // Memeriksa apakah sensor berhasil mambaca suhu dan kelembaban
  if (isnan(t) || isnan(h)) {
    Serial.println("Gagal membaca sensor DHT11");
    delay(1000);
    return;
  }

  // Menampilkan suhu dan kelembaban kepada serial monitor
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  // Memberikan status suhu dan kelembaban kepada firebase
  if (Firebase.setFloat(firebaseData, "/Data/suhu", t)){
      Serial.println("Suhu terkirim");
    } else{
      Serial.println("Suhu tidak terkirim");
      Serial.println("Karena: " + firebaseData.errorReason());
    }
   
  if (Firebase.setFloat(firebaseData, "/Data/kelembaban", h)){
      Serial.println("Kelembaban terkirim");
      Serial.println();
    } else{
      Serial.println("Kelembaban tidak terkirim");
      Serial.println("Karena: " + firebaseData.errorReason());
    }
 
   
  delay(1000);
}