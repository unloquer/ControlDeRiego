/*

 Udp NTP Client

 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket
 For more on NTP time servers and the messages needed to communicate with them,
 see http://en.wikipedia.org/wiki/Network_Time_Protocol

 created 4 Sep 2010
 by Michael Margolis
 modified 9 Apr 2012
 by Tom Igoe
 updated for the ESP8266 12 Apr 2015
 by Ivan Grokhotkov

 This code is in the public domain.

 */
#include "Arduino.h"
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "C3P";
const char *password = "trespatios";

#define RIEGO_PIN 4

WiFiUDP ntpUDP;

// By default 'time.nist.gov' is used.
NTPClient timeClient(ntpUDP);

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient("europe.pool.ntp.org", 3600, 60000);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  pinMode(RIEGO_PIN, OUTPUT);
  //timeClient.begin();
}

void loop() {
  timeClient.update();

  //Serial.println(timeClient.getFormattedTime());
  Serial.println(timeClient.getHours()+":"+timeClient.getMinutes()+":"+timeClient.getSeconds()) ;
  //Colombia UTM -5

  if (timeClient.getHours()  == "22") {

    if(timeClient.getMinutes() == "20")
      {
        digitalWrite(RIEGO_PIN, HIGH);
        Serial.println("Regando");
      }
    if(timeClient.getMinutes() == "25")
      {
        digitalWrite(RIEGO_PIN, LOW);
        delay(1000);
      }
  }

  delay(1000*30);
}

/*
#include <ESP8266WiFi.h>
const char* SSID = "C3P";
const char* PASS = "trespatios";
char server[] = "smtp.gmail.com";

byte eRcv();
byte sendEmail();

WiFiClient client;
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting To ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  byte ret = sendEmail();
}

void loop()
{
}

byte sendEmail()
{
  byte thisByte = 0;
  byte respCode;

  if (client.connect(server, 587) == 1) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }
  if (!eRcv()) return 0;

  Serial.println(F("Sending EHLO"));
  client.println("EHLO www.example.com");
  if (!eRcv()) return 0;
  Serial.println(F("Sending auth login"));
  client.println("auth login");
  if (!eRcv()) return 0;
  Serial.println(F("Sending User"));
  // Change to your base64, ASCII encoded user
  // https://www.base64encode.org/
  client.println("dW5sb3F1ZXJAZ21haWwuY29t"); //<---------User
  if (!eRcv()) return 0;
  Serial.println(F("Sending Password"));
  // change to your base64, ASCII encoded password
  client.println("dW5sMHF1M3I=");//<---------Passw
  if (!eRcv()) return 0;
  Serial.println(F("Sending From"));
  // change to your email address (sender)
  client.println(F("MAIL From: jardin@unloquer.org"));
  if (!eRcv()) return 0;
  // change to recipient address
  Serial.println(F("Sending To"));
  client.println(F("RCPT To: unloquer@lists.aktivix.org"));
  if (!eRcv()) return 0;
  Serial.println(F("Sending DATA"));
  client.println(F("DATA"));
  if (!eRcv()) return 0;
  Serial.println(F("Sending email"));
  // change to recipient address
  client.println(F("To:  unloquer@lists.aktivix.org"));
  // change to your address
  client.println(F("From: jardin@unloquer.org"));
  client.println(F("Subject: Estoy regando el jardín\r\n"));
  client.println(F("ESP8266 regando jardín de la casa\n"));

  client.println(F("."));
  if (!eRcv()) return 0;
  Serial.println(F("Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv()) return 0;
  client.stop();
  Serial.println(F("disconnected"));
  return 1;
}

byte eRcv()
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;

  while (!client.available()) {
    delay(1);
    loopCount++;
    // if nothing received for 10 seconds, timeout
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }

  if (respCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}
*/
