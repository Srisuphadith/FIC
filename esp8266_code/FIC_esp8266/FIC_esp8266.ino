/**
   PostHTTPClient.ino

    Created on: 21.11.2016

*/
#include "DHTesp.h"
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY !)
#error Select ESP8266 board.
#endif
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
DHTesp dht;
#define SEND_DATA "http://helloworld.3bbddns.com:42240/data_upload"  //forward port for test
//#define SEND_DATA "http://host/data_upload"
#define RECEIVE_DATA "http://helloworld.3bbddns.com:42240/data_request"  //forward port for test
//#define RECEIVE_DATA "http://host/data_request"
#ifndef STASSID
#define STASSID "KAI@2.4G"
#define STAPSK "33479102"
#endif

//Prototype  functions--------------------------------------------------------
void HTTP_POST(char url[], float temperature, float humidity, float soil_sensor);
void HTTP_GET(char url[]);
//Prototype  functions--------------------------------------------------------
// output port------------
#define pump 12  //0 to open, 1 to close
#define fan 14   //0 to open, 1 to clsoe
// output port------------
// state for database---------------
int pump_state = 1;
int fan_state = 1;
// state for database---------------
#include <Arduino_JSON.h>
const int analogInPin = A0;
int time_count = 0;
int sensorReadingsArr[3];
void setup() {
  pinMode(fan, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(fan, fan_state);    // init fan state
  digitalWrite(pump, pump_state);  // init pump state
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);
  dht.setup(4, DHTesp::DHT11);
  WiFi.begin(STASSID, STAPSK);
  //exit loop if wifi connected
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
  //delay(dht.getMinimumSamplingPeriod());
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
    if (time_count >= 30) {
      HTTP_POST(SEND_DATA, temperature, humidity, soil_sensor);
      time_count = 0;
    }
    HTTP_GET(RECEIVE_DATA);
    digitalWrite(fan, !fan_state);    // control fan state
    digitalWrite(pump, !pump_state);  // control pump state
  }

  delay(1000);
  time_count++;
}
//---------------------------functions----------------------------
void HTTP_POST(char url[], float temperature, float humidity, float soil_sensor) {
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(client, url);  // HTTP
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
  String data = "{\"temperature\":\"" + tmp + "\"" + ",\"humidity\":\"" + hum + "\",\"soil_humidity\":\"" + soil + "\"}";
  Serial.println(data);
  //create request with POST methods
  int httpCode = http.POST(data);

  // httpCode will be negative on error
  if (httpCode > 0) {
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
void HTTP_GET(char url[]) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    //Serial.println(payload);
    //string to JSON
    JSONVar myObject = JSON.parse(payload);
    pump_state = myObject[0][1];
    fan_state = myObject[0][2];
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
