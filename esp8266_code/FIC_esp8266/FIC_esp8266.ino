/**
   PostHTTPClient.ino

    Created on: 21.11.2016

*/
#include "DHTesp.h"
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
DHTesp dht;
/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/
//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "http://helloworld.3bbddns.com:42240/data_upload"
//#define SERVER_IP "https://helloworld.3bbddns.com:42240/data_upload"
#ifndef STASSID
#define STASSID "KAI@2.4G"
#define STAPSK "33479102"
#endif
const int analogInPin = A0;
void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  dht.setup(4, DHTesp::DHT11);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //------------------------------------------------
  delay(dht.getMinimumSamplingPeriod());
  // input humidity from DHT11
  float humidity = dht.getHumidity();
  // input temperature from DHT11
  float temperature = dht.getTemperature();
  // input soil humidity
  int soil_sensor = analogRead(analogInPin);
  //map value of analog from 1024-0 to 0-100
  soil_sensor = map(soil_sensor, 0, 1024, 100, 0);
  //------------------------------------------------

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, SERVER_IP);  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    //create string 
    String tmp = "";
    String hum = "";
    String soil = "";
    //convert float/int to string for string concatenation 
    tmp += temperature;
    hum += humidity;
    soil += soil_sensor;
    // merge string to json from
    String data = "{\"temperature\":\""+tmp+"\""+",\"humidity\":\""+hum+"\",\"soil_humidity\":\""+soil+"\"}";
    //create request with POST methods
    int httpCode = http.POST(data);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(5000);
}
