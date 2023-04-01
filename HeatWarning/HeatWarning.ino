#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPLOenLUNIg"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "OIn40IHS43dLusA2OekALqzmEVqB17Rb"

char ssid[] = "12345";
char pass[] = "12345678900";

const int DHT11PIN = D2;
const int DHTTYPE = DHT11;

DHT dht(DHT11PIN, DHTTYPE);
double h, tc;
WidgetLED led1(V2);

void setup() {
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("*");
  }
  dht.begin();
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());  // Print the IP address
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  //
  Blynk.run();
  h = dht.readHumidity();
  tc = dht.readTemperature();
  if (isnan(h) || isnan(tc)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(1000);
    return;
  }
  Serial.println(h);
  Serial.println("_______");
  Serial.println(tc);
  Serial.println("_______");
  if (h > 70 || tc > 32) {
    led1.on();
    Blynk.logEvent("heat_warning","Temperture higher than 100 or Humidity higher than 90");
    delay(500);
  } else {
    led1.off();
  }
  Blynk.virtualWrite(V1, tc);
  Blynk.virtualWrite(V4, h);
  delay(1000);
}
