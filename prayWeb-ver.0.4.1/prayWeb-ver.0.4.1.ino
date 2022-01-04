/*
   ESP8266 (NodeMCU) Handling Web form data basic example
   <a href="https://circuits4you.com">https://circuits4you.com</a>
*/
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
//#include "WiFiTerm.h"
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <Ticker.h>
//#include <Effortless_SPIFFS.h>

#define VERSION "ver. 0.4"
char MASJID[48];
char ALAMAT[128];
char LATITUDE[16];// = "-6.931706";
char LONGITUDE[16];// = "107.561833";
char BRIGHTVAL[2];
char SPEEDVAL[2];
//kediri -7.8140281,111.9780112
typedef enum idx {
  spiWrt = 0, vers, mosq, madd, lati, lont, brig, spee, last
};
idx spiIndex;

AsyncWebServer server(80);
String message, buff;
//const char* PARAM_MESSAGE = "message";

//SSID and Password of your WiFi router
//char* ssid = "Androido";
//char* password = "tkvo8562";
char ssid[24] = "JamSholat_";
char* password = "12345678";
char lastTime[24];

IPAddress local_ip(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

//IPAddress remot(192, 168, 43, 236);
IPAddress remot(192, 168, 0, 2);
WiFiUDP Udp;
unsigned int localPort = 8888;      // local port to listen on
unsigned int remotPort = 1230;
//char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
//char  ReplyBuffer[] = "Mulai";       // a string to send back
char inputChar[512];
String inputString = "", termBuff;

Ticker blinker;
#define maxLifeTick 360
File f;
//eSPIFFS fileSystem;

//==============================================================
//                  SETUP
//==============================================================
void setup(void) {

  char buffMac[3];
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  //  if (!SPIFFS.begin()) {
  //    //    Serial.println("An Error has occurred while mounting SPIFFS");
  //    return;
  //  }
  SPIFFS.begin();
  loadRom();
  delay(1000);

  //  eSPIFFS fileSystem;
  uint8_t macAddr[6];
  WiFi.macAddress(macAddr);
  itoa (macAddr[3], buffMac, 16);
  strcat(ssid, buffMac);
  itoa (macAddr[4], buffMac, 16);
  strcat(ssid, buffMac);
  itoa (macAddr[5], buffMac, 16);
  strcat(ssid, buffMac);


  WiFi.softAPConfig (local_ip, gateway, subnet);
  WiFi.softAP(ssid, password, 1, false, 1);
  /*
      WiFi.begin(ssid, password);     //Connect to your WiFi router
      Serial.print("\nssid: "); Serial.println(ssid);
    //   Wait for connection
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

    If connection successful show IP address in serial monitor
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println("WiFi");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  */
  if (!MDNS.begin("jamsholat")) {
    //    Serial.println("Error setting up MDNS responder!");
    //    while (1) {
    //      delay(1000);
    //    }
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
    //    Serial.write(0x02);
    Serial.print("US");
    Serial.println();
    //    Serial.write(0x03);
  });
  server.on("/mosque.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/mosque.png", "image/png");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/masjid", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/wifi.html", String(), false, processor);
  });

  server.on("/mosque_conf", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("masjid", true)) {
      message = request->getParam("masjid", true)->value();
      message.toCharArray(MASJID, 48);
      writeROM(MASJID, mosq);
      message += ", ";
    }
    //    Serial.println(MASJID);
    if (request->hasParam("alamat", true)) {
      buff = request->getParam("alamat", true)->value();
      message += buff;
      buff.toCharArray(ALAMAT, 128);
      writeROM(ALAMAT, madd);
    }
    //    Serial.println(ALAMAT);
    Serial.print("MJ,");
    Serial.print(message);
    Serial.println();
    request->send(SPIFFS, "/wifi.html", String(), false, processor);
  });

  server.on("/coordinate_conf", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("lat", true)) {
      message = request->getParam("lat", true)->value();
      message.toCharArray(LATITUDE, sizeof(message));
      writeROM(LATITUDE, lati);
      message += ",";
    }
    //    double lat = atof(LATITUDE);
    //    Serial.println(lat,5);
    if (request->hasParam("long", true)) {
      buff = request->getParam("long", true)->value();
      message += buff;
      buff.toCharArray(LONGITUDE, sizeof(buff));
      writeROM(LONGITUDE, lont);
    }
    //    double lon = atof(LONGITUDE);
    //    Serial.println(lon,5);
    Serial.print("LL,");
    Serial.print(message);
    Serial.println();
    request->send(SPIFFS, "/wifi.html", String(), false, processor);
  });

  server.on("/gps_page", HTTP_POST, [](AsyncWebServerRequest * request) {
    Serial.println("gps");
    request->send(SPIFFS, "/wifi.html", String(), false, processor);
  });

  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("reboot");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/sync_page", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("date", true)) {
      message = request->getParam("date", true)->value();
    } else {
      //      message = "No message sent";
    }
    if (request->hasParam("fdate", true)) {
      buff = request->getParam("fdate", true)->value();
      buff.toCharArray(lastTime, buff.length() + 1);
      writeROM(lastTime, last);
    }
    //        Serial.write(0x02);
    Serial.print("T,");
    Serial.print(message);
    Serial.println();
    //        Serial.println(lastTime);
    //    Serial.write(0x03);

    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/bright_page", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("bright", true)) {
      buff = request->getParam("bright", true)->value();
      buff.toCharArray(BRIGHTVAL, sizeof(buff));
      writeROM(BRIGHTVAL, brig );
    } else {
      //      message = "No message sent";
    }
    //    Serial.write(0x02);
    Serial.print("B,");
    Serial.print(buff);
    Serial.println();
    //    Serial.write(0x03);

    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/text_page", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("speed", true)) {
      buff = request->getParam("speed", true)->value();
      buff.toCharArray(SPEEDVAL, sizeof(buff));
      writeROM(SPEEDVAL, spee);
    }
    //    Serial.write(0x02);
    Serial.print("S,");
    Serial.print(buff);
    Serial.println();
    //    Serial.write(0x03);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  if (!MDNS.begin("jamsholat")) {
    //    Serial.println("Error setting up MDNS responder!");
    //    while (1) {
    //      delay(1000);
    //    }
  }
  server.begin();                  //Start server
  //  term.begin(server);
  //  Serial.println("term started");
  //  Serial.println("HTTP server started");
  Udp.begin(localPort);
  blinker.attach(1, Tick);

  MDNS.addService("http", "tcp", 80);
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  //  server.handleClient();          //Handle client requests
  MDNS.update();
  if (Serial.available() > 0) {
    char inChar = (char) Serial.read();
    if ((inChar >= 32) && (inChar < 127)) {
      inputString += inChar;
    }
    if (inChar == '\n') {
      //      UART.println(inputString);
      inputString.toCharArray(inputChar, sizeof(inputString));
      Udp.beginPacket(remot, remotPort);
      Udp.write(inputChar);
      Udp.endPacket();

      inputString.toCharArray(inputChar, sizeof(inputString));
      Udp.beginPacket(remot, remotPort);
      Udp.write(inputChar);
      Udp.endPacket();

      inputString = "";
    }
  }
}

String processor(const String & var) {
  //  Serial.println(var);
  if (var == "VERSION") {
    return VERSION;
  } else if (var == "MASJID") {
    return MASJID;
  } else if (var == "ALAMAT") {
    return ALAMAT;
  } else if (var == "LATITUDE") {
    return LATITUDE;
  } else if (var == "LONGITUDE") {
    return LONGITUDE;
  } else if (var == "SSID") {
    return ssid;
  } else if (var == "LASTTIME") {
    return lastTime;
  } else if (var == "BRIGHTVAL") {
    return BRIGHTVAL;
  } else if (var == "SPEEDVAL") {
    return SPEEDVAL;
  }
}
void Tick() {
  static int tick;
  tick++;
  if (tick > maxLifeTick) {
    //    Serial.write(0x02);
    Serial.print("WOFF");
    Serial.println();
    //    Serial.write(0x03);
    tick = 0;
  }
}
