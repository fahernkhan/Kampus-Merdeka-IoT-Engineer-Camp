#define BLYNK_TEMPLATE_ID "TMPL6BXca_AfW"
#define BLYNK_TEMPLATE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "UscQqqg9Z_QVsd8Gws-Iu1oUjLGfzzbL"
#include <ESP8266WiFi.h> // include library
#include <BlynkSimpleEsp8266.h> // include library
#include <DHT.h> //Library untuk DHT
#define DHTPIN D3 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = "UscQqqg9Z_QVsd8Gws-Iu1oUjLGfzzbL"; //Auth Token
char ssid[] = "MiExtender"; //nama hotspot yang digunakan
char pass[] = "Fafa123vydisfasamson"; //password hotspot yang digunakan
//function untuk pengiriman sensor
void sendSensor()
{
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");
Blynk.virtualWrite(V2, t); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V3, h); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud
}
void setup() {
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
Blynk.begin(auth, ssid, pass); //memulai Blynk
dht.begin(); //mengaktifkan DHT11
timer.setInterval(1000L, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}
void loop() {
Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}