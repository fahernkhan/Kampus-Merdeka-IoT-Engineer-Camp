#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>


const char* ssid = "";
const char* password = "";
FirebaseData firebaseData;

int led = D6;

void setup() {
Serial.begin(9600);
pinMode(led, OUTPUT);
digitalWrite(led, LOW); //nilai awal relay akan off
 
WifiConnect();
  Firebase.begin("https://kendali-led-1f842-default-rtdb.firebaseio.com/", "JsEHTBElM9fQGQ8X9KzuvGqy9COH33NZH78xIqn7");
  //Firebase.begin("firebase host", "firebase auth database");
}

void WifiConnect() {
WiFi.begin(ssid, password);
//memulai menghubungkan ke wifi router
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("."); //status saat mengkoneksikan
  }
Serial.println("Sukses terkoneksi wifi!");
Serial.println("IP Address:"); //alamat ip lokal
Serial.println(WiFi.localIP());
}

void loop() {
  if (Firebase.getString(firebaseData, "/Led")) {
  if  (firebaseData.dataType() == "string")
    {
      String Status = firebaseData.stringData();
      if (Status == "ON") {                                                        
      Serial.println("Led Menyala");                        
      digitalWrite(led, HIGH); }
      else if (Status == "OFF") {                                                 
      Serial.println("led Mati");
      digitalWrite(led, LOW);                                               
      }
      else {Serial.println("Silahkan hanya isi dengan ON atau OFF");}
    }
  }
}