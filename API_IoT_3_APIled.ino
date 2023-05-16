#define BLYNK_PRINT Serial
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6BXca_AfW"
#define BLYNK_TEMPLATE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "UscQqqg9Z_QVsd8Gws-Iu1oUjLGfzzbL"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MiExtender";
char password[] ="Fafa123vydisfasamson";
#define led1 D2
#define led2 D3
BLYNK_WRITE(V0)
{
int pinValue = param.asInt();
digitalWrite(led1,pinValue);
}
BLYNK_WRITE(V1)
{
int pinValue1 = param.asInt();
digitalWrite(led2,pinValue1);
}
void setup()
{
// Debug console
Serial.begin(9600);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
Blynk.begin(auth,ssid,password);
// Setup a function to be called every second
}
void loop()
{
Blynk.run();
}