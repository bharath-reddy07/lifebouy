#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST "lifebuoy-8161b-default-rtdb.firebaseio.com"  //Without http:// or https:// schemes
#define FIREBASE_AUTH "2AkdLjZWXHpP5k2qLOYCrejTMsjDnRfuuE7Lfa07"
#define WIFI_SSID "test"
#define WIFI_PASSWORD "12345678"

FirebaseData firebaseData;
FirebaseData Data;

FirebaseJson json;
int ind1, ind2;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
String hrMin = "", curDay = "", monthYr = "", epoch = "";

void setup() {

  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  timeClient.begin();
  timeClient.setTimeOffset((5 * 60 + 30) * 60);
}
void loop() {
  //Firebase.set(firebaseData, "/users/sindhu/", 4);

  getTime();
  while (Serial.available()) {
    String readStr = String(Serial.readString());
    String sub = "";

    while (readStr.length() > 2) {
      ind1 = readStr.indexOf(',');
      sub = readStr.substring(0, ind1);
      readStr = readStr.substring(ind1 + 1);
      Serial.println(sub);
      Firebase.setString(firebaseData, "/test/" + String(epoch) + "/" + sub.substring(0, sub.indexOf(':')), sub.substring(sub.indexOf(':') + 1));
    }


    Firebase.setString(firebaseData, "/test/" + String(epoch), readStr);
    //    Serial.print("/test/" + epoch + "/");
    //    Serial.println(readStr);
  }
}

void getTime() {

  timeClient.update();

  int currentHour = timeClient.getHours();

  int currentMinute = timeClient.getMinutes();

  time_t epochTime = timeClient.getEpochTime();
  epoch = String(epochTime);
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;

  int currentMonth = ptm->tm_mon + 1;

  int currentYear = ptm->tm_year + 1900;

  monthYr = String(currentMonth) + "-" + String(currentYear);
  curDay = String(monthDay);
  hrMin = String(currentHour) + String(currentMinute);
  //Serial.println(monthYr + "\n" + curDay + "\n" + hrMin);


  return;
}


//Firebase.setInt(firebaseData, "temp", temp);
