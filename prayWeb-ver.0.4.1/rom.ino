void loadRom() {
  String strBuff;
  //  File f = SPIFFS.open("/masjid.txt", MASJID);
  //  File f = SPIFFS.open("/version.txt", VERSION);
  f = SPIFFS.open("/masjid.txt", "r"); // MASJID);

  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(MASJID, strBuff.length() + 1);
  strBuff = "";

  f = SPIFFS.open("/alamat.txt", "r"); //,
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(ALAMAT, strBuff.length() + 1);
  strBuff = "";

  f = SPIFFS.open("/longitude.txt", "r"); //,
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(LONGITUDE, strBuff.length() + 1);
  strBuff = "";

  f = SPIFFS.open("/latitude.txt", "r"); //,
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(LATITUDE, strBuff.length() + 1);
  strBuff = "";
 
  f = SPIFFS.open("/brightness.txt", "r"); //
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(BRIGHTVAL, strBuff.length() + 1);
  strBuff = "";

  f = SPIFFS.open("/speed.txt", "r");    //
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(SPEEDVAL, strBuff.length() + 1);
  strBuff = "";

  f = SPIFFS.open("/lasttime.txt", "r"); //
  while (f.available()) {
    strBuff += char(f.read());
  }
  f.close();
  strBuff.toCharArray(lastTime, strBuff.length() + 1);
  strBuff = "";

}

void writeROM(char *charData, idx address) {
  switch (address) {
    case spiWrt:
      //      f = SPIFFS.open("/String.txt", "w");//, newString);
      break;
    case vers:
      //     f = SPIFFS.open("/version.txt", "w");//, VERSION);
      break;
    case mosq:
      f = SPIFFS.open("/masjid.txt", "w");//,
      f.print(charData);
      f.close();
      break;
    case madd:
      f = SPIFFS.open("/alamat.txt", "w");//,
      f.print(charData);
      f.close();
      break;
    case lati:
      f = SPIFFS.open("/latitude.txt", "w");//,
      f.print(charData);
      f.close();
      break;
    case lont:
      f = SPIFFS.open("/longitude.txt", "w");//,
      f.print(charData);
      f.close();
      break;   
    case brig:
      f = SPIFFS.open("/brightness.txt", "w");//,
      f.print(BRIGHTVAL);
      f.close();
      break;
    case spee:
      f = SPIFFS.open("/speed.txt", "w");//,
      f.print(SPEEDVAL);
      f.close();
      break;
    case last:
      f = SPIFFS.open("/lastime.txt", "w");//,
      f.print(lastTime);
      f.close();
      break;

  }

}

void readROM(char* data) {

}
