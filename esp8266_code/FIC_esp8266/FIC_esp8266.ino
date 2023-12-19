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
#define Token "fe4a5dbf3f300bb6bdcbc09be5246115fdd2c316a077dddd8f72e349cd7ee2a4"
#endif

//Prototype  functions--------------------------------------------------------
void HTTP_POST(char url[], float temperature, float humidity, float soil_sensor);
void HTTP_GET(char url[]);
void output(float temperature, float soil_sensor, float humidity);
//Prototype  functions--------------------------------------------------------
// output port------------
#define pump 12  //0 to open, 1 to close
#define fan 14   //0 to open, 1 to clsoe
// output port------------
// state for database---------------
int pump_state = 1;
int fan_state = 1;
int pump_max_temp = 30;
int pump_min_temp = 25;
int pump_max_humi = 50;
int fan_min_temp = 40;
int fan_min_humi = 75;
// state for database---------------
#include <Arduino_JSON.h>
const int analogInPin = A0;
int time_count = 0;
int tigger = 0;
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

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}
int n = 0;
int c = 0;
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
  Serial.print("Temp = ");
  Serial.println(temperature);
  Serial.print("soil = ");
  Serial.println(soil_sensor);
  //wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    if (time_count >= 30) {
      HTTP_POST(SEND_DATA, temperature, humidity, soil_sensor);
      time_count = 0;
    }
    HTTP_GET(RECEIVE_DATA);
    if (tigger == 0) {
      digitalWrite(fan, !fan_state);    // control fan state
      digitalWrite(pump, !pump_state);  // control pump state
    }

    time_count++;
    //------------------------ while wifi connected
    output(temperature, soil_sensor, humidity);
    //------------------------ while wifi connected

  } else {
    //---------------------------- if wifi not connected
    output(temperature, soil_sensor, humidity);
    //---------------------------- if wifi not connected
  }

  delay(1000);
}
//---------------------------functions----------------------------

//---------------------POST-----------------------------------
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
  String data = "{\"temperature\":\"" + tmp + "\"" + ",\"humidity\":\"" + hum + "\",\"soil_humidity\":\"" + soil + "\",\"token\":\""+Token+"\"}";
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
//---------------------GET-----------------------------------
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
    pump_max_temp = myObject[0][3];
    pump_min_temp = myObject[0][4];
    pump_max_humi = myObject[0][5];
    fan_min_temp = myObject[0][6];
    fan_min_humi = myObject[0][7];
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
//---------------------control output-----------------------------------
void output(float temperature, float soil_sensor, float humidity) {
  //fan
  if (temperature > fan_min_temp || humidity > fan_min_humi) {
    digitalWrite(fan, 0);
    tigger = 1;
  } else {
    digitalWrite(fan, 1);
    tigger = 0;
  }
  //pump
  if ((soil_sensor <= pump_max_humi) && (temperature >= pump_min_temp && temperature <= pump_max_temp) && n == 0) {
    digitalWrite(pump, 0);
    delay(10000);
    n = 1;
    tigger = 1;
  } else {
    digitalWrite(pump, 1);
    tigger = 0;
    if (n == 1) {
      c++;
    }
    //Serial.println(c);
    if (c >= 60) {
      n = 0;
      c = 0;
    }
  }
}
