/////////////////// Buffers //////////////////////////
char buff_jam[3], buff_mnt[3], buff_tanggal[3], buff_bulan[6], buff_tahun[5];
char buff_iqoDtk[3], buff_iqoMnt[3];
char buff_iqoSub[3], buff_iqoDzu[3], buff_iqoAsh[3], buff_iqoMag[3], buff_iqoIsy[3];
char buff_subuh[6], buff_dzuhur[6], buff_ashar[6], buff_maghrib[6], buff_isya[6];
char buff_syuruq[6], buff_dhuha[6];
char buff_bright[2], buff_speed[2];
char buff_lat[10], buff_long[10];
/////////////////// ////// //////////////////////////

char vHari[7][7] = {
  {'A', 'h', 'a', 'd'},
  {'S', 'e', 'n', 'i', 'n'},
  {'S', 'e', 'l', 'a', 's', 'a'},
  {'R', 'a', 'b', 'u'},
  {'K', 'a', 'm', 'i', 's'},
  {'J', 'u', 'm', 'a', 't'},
  {'S', 'a', 'b', 't', 'u'}
};

char vBulan[12][10] = {
  {'J', 'a', 'n', 'u', 'a', 'r', 'i'},
  {'F', 'e', 'b', 'r', 'u', 'a', 'r', 'i'},
  {'M', 'a', 'r', 'e', 't'},
  {'A', 'p', 'r', 'i', 'l'},
  {'M', 'e', 'i'},
  {'J', 'u', 'n', 'i'},
  {'J', 'u', 'l', 'i'},
  {'A', 'g', 'u', 's', 't', 'u', 's'},
  {'S', 'e', 'p', 't', 'e', 'm', 'b', 'e', 'r'},
  {'O', 'k', 't', 'o', 'b', 'e', 'r'},
  {'N', 'o', 'v', 'e', 'm', 'b', 'e', 'r'},
  {'D', 'e', 's', 'e', 'm', 'b', 'e', 'r'}
};
////////////////////////////////////////////////////

void hourToBuff() {

  uint8_t vhour;
  uint8_t vmin;
  vhour = ((uint8_t) waktu->tm_hour) / 10;
  buff_jam[0]  = (char) vhour + 48;
  buff_jam[1] = (char) (((uint8_t) waktu->tm_hour) % 10) + 48;
  vmin = ((uint8_t) waktu->tm_min) / 10;
  buff_mnt[0] = (char)  vmin + 48;
  buff_mnt[1] = (char) (((uint8_t) waktu->tm_min) % 10) + 48;

}

void minToBuff() {
  uint8_t vmin;
  vmin = ((uint8_t) waktu->tm_min) / 10;
  buff_mnt[0] = (char)  vmin + 48;
  buff_mnt[1] = (char) (((uint8_t) waktu->tm_min) % 10) + 48;
}

void dateBuff() {
  uint8_t vtggl;
  uint16_t vthn;
  vtggl = ((uint8_t) waktu->tm_mday / 10);
  buff_tanggal[0] = (char)  vtggl + 48;
  buff_tanggal[1] = (char)  (((uint8_t) waktu->tm_mday) % 10) + 48;

  vthn  = ((uint16_t)(waktu->tm_year + 1900));
  buff_tahun[0] = (uint8_t)(vthn / 1000) + 48;
  buff_tahun[1] = (uint8_t)((vthn % 1000) / 100) + 48;
  buff_tahun[2] = (uint8_t)((vthn % 100) / 10) + 48;
  buff_tahun[3] = (uint8_t)(vthn % 10) + 48;

  buff_bulan[0] = vBulan[waktu->tm_mon][0];
  buff_bulan[1] = vBulan[waktu->tm_mon][1];
  buff_bulan[2] = vBulan[waktu->tm_mon][2];
  buff_bulan[3] = vBulan[waktu->tm_mon][3];
  buff_bulan[4] = vBulan[waktu->tm_mon][4];

}

void menuBuff() {
  buff_bright[0] = (brightVal / 10) + 48;
  buff_bright[1] = (brightVal % 10) + 48;
  buff_speed[0] = (textSpeed / 10) + 48;
  buff_speed[1] = (textSpeed % 10) + 48;
  buff_iqoSub[0] = (iqoSub / 10) + 48;
  buff_iqoSub[1] = (iqoSub % 10) + 48;
  buff_iqoDzu[0] = (iqoDzu / 10) + 48;
  buff_iqoDzu[1] = (iqoDzu % 10) + 48;
  buff_iqoAsh[0] = (iqoAsh / 10) + 48;
  buff_iqoAsh[1] = (iqoAsh % 10) + 48;
  buff_iqoMag[0] = (iqoMag / 10) + 48;
  buff_iqoMag[1] = (iqoMag % 10) + 48;
  buff_iqoIsy[0] = (iqoIsy / 10) + 48;
  buff_iqoIsy[1] = (iqoIsy % 10) + 48;
}

void loadRom() {
  iqoSub = (int8_t) EEPROM.read(SubAddr);
  iqoDzu = (int8_t) EEPROM.read(DzuAddr);
  iqoAsh = (int8_t) EEPROM.read(AshAddr);
  iqoMag = (int8_t) EEPROM.read(MagAddr);
  iqoIsy = (int8_t) EEPROM.read(IsyAddr);
  brightVal = (int8_t) EEPROM.read(BrgAddr);
  textSpeed = (int8_t) EEPROM.read(SpdAddr);
  
  memset(latBuff, '\0', 16);
  memset(longBuff, '\0', 16);
  for (int idx = 0; idx < 16 ; idx++) {
    latBuff[idx] =(char) EEPROM.read(LatAddr + idx);
  }
  Latitude = atof(latBuff);
//  USART.print("lat in buff: ");
//  USART.println(latBuff);
//  USART.print("lat in float: ");
//  USART.println(Latitude,5);
  for (int idx = 0; idx < 16; idx++) {
    longBuff[idx] =(char) EEPROM.read(LongAddr + idx);
  }
  Longitude = atof(longBuff);
//  USART.print("long in buff: ");
//  USART.println(longBuff);
//  USART.print("long in float: ");
//  USART.println(Longitude,5);
  
  memset(NAMA_MASJID, '\0', 80);
    for (int idx = 0; idx < 80; idx++) {
    NAMA_MASJID[idx] =(char) EEPROM.read(MjdAddr + idx);
  }
//  USART.print("masjid: ");
//  USART.println(NAMA_MASJID);
}

void iqomahBuff() {
  uint8_t tmp_mnt, tmp_dtk;
  if (sholat == subuh) {
    tmp_mnt = (iqoSubTimeout - cur_tstamp) / 60;
    tmp_dtk = (iqoSubTimeout - cur_tstamp) % 60;
  } else if (sholat == dzuhur) {
    tmp_mnt = (iqoDzuTimeout - cur_tstamp) / 60;
    tmp_dtk = (iqoDzuTimeout - cur_tstamp) % 60;
  } else if (sholat == ashar) {
    tmp_mnt = (iqoAshTimeout - cur_tstamp) / 60;
    tmp_dtk = (iqoAshTimeout - cur_tstamp) % 60;
  } else if (sholat == maghrib)  {
    tmp_mnt = (iqoMagTimeout - cur_tstamp) / 60;
    tmp_dtk = (iqoMagTimeout - cur_tstamp) % 60;
  } else if (sholat == isya)  {
    tmp_mnt = (iqoIsyTimeout - cur_tstamp) / 60;
    tmp_dtk = (iqoIsyTimeout - cur_tstamp) % 60;
  }
  buff_iqoMnt[0] = (tmp_mnt / 10) + 48;
  buff_iqoMnt[1] = (tmp_mnt % 10) + 48;
  buff_iqoDtk[0] = (tmp_dtk / 10) + 48;
  buff_iqoDtk[1] = (tmp_dtk % 10) + 48;
}


void topBufferProc() {
  dateBuff();
  matrix.selectFont(font5x7);
  memset(infoText[praySeq], '\0', 128);
  strcpy(infoText[praySeq], "Subuh`");
  strcat(infoText[praySeq], buff_subuh);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "Syuruq`");
  strcat(infoText[praySeq], buff_syuruq);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "Dhuha`");
  strcat(infoText[praySeq], buff_dhuha);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "Dzuhur`");
  strcat(infoText[praySeq], buff_dzuhur);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "'Ashr`");
  strcat(infoText[praySeq], buff_ashar);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "Maghrib`");
  strcat(infoText[praySeq], buff_maghrib);
  strcat(infoText[praySeq], "`*`");
  strcat(infoText[praySeq], "'Isya`");
  strcat(infoText[praySeq], buff_isya);

  strcat(infoText[praySeq], "\0");
  topPixLimit[praySeq] = matrix.countPixelChar(infoText[praySeq]);
  messageLenght[praySeq] = matrix.totalChar;

  if (sholat != idle) {
    memset(infoText[flickSeq], '\0', 128);

    if (sholat == subuh) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcpy(infoText[flickSeq], "Subuh`");
      strcat(infoText[flickSeq], "##:");
      if (buff_subuh[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_subuh[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcpy(infoText[flickSeq], "Subuh`");
      strcat(infoText[flickSeq], buff_subuh);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == syuruq) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "Syuruq`");
      strcat(infoText[flickSeq], "##:");
      if (buff_syuruq[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_syuruq[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "Syuruq`");
      strcat(infoText[flickSeq], buff_syuruq);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == dhuha) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "Dhuha`");
      strcat(infoText[flickSeq], "##:");
      if (buff_dhuha[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_dhuha[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "Dhuha`");
      strcat(infoText[flickSeq], buff_dhuha);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == dzuhur) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "Dzuhur`");
      strcat(infoText[flickSeq], "$");
      if (buff_dzuhur[1] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      strcat(infoText[flickSeq], ":");
      if (buff_dzuhur[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_dzuhur[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "Dzuhur`");
      strcat(infoText[flickSeq], buff_dzuhur);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == ashar) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "'Ashr`");
      strcat(infoText[flickSeq], "$#:");
      if (buff_ashar[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_ashar[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "'Ashr`");
      strcat(infoText[flickSeq], buff_ashar);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == maghrib) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "Maghrib`");
      strcat(infoText[flickSeq], "$#:");
      if (buff_maghrib[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_maghrib[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "Maghrib`");
      strcat(infoText[flickSeq], buff_maghrib);
    }
    strcat(infoText[flickSeq], "`*`");

    if (sholat == isya) {
      startSlowPix = matrix.countPixelChar(infoText[flickSeq]);
      strcat(infoText[flickSeq], "'Isya`");
      strcat(infoText[flickSeq], "$#:");
      if (buff_isya[3] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      if (buff_isya[4] == '1')
        strcat(infoText[flickSeq], "$");
      else
        strcat(infoText[flickSeq], "#");
      endSlowPix = matrix.countPixelChar(infoText[flickSeq]);
    } else {
      strcat(infoText[flickSeq], "'Isya`");
      strcat(infoText[flickSeq], buff_isya);
    }
    strcat(infoText[flickSeq], "\0");

    topPixLimit[flickSeq] = matrix.countPixelChar(infoText[flickSeq]);
    messageLenght[flickSeq] = matrix.totalChar;
  }

  matrix.selectFont(font5x7);
  memset(infoText[dateSeq], 0, 64);
  strcpy(infoText[dateSeq], vHari[waktu->tm_wday]);
  strcat(infoText[dateSeq], ",`");
  strcat(infoText[dateSeq], buff_tanggal);
  strcat(infoText[dateSeq], "`");
  strcat(infoText[dateSeq], vBulan[waktu->tm_mon]);
  strcat(infoText[dateSeq], "`");
  strcat(infoText[dateSeq], buff_tahun);
  strcat(infoText[dateSeq], "\0");
  topPixLimit[dateSeq] = matrix.countPixelChar(infoText[dateSeq]);
  messageLenght[dateSeq] = matrix.totalChar;
}

void customBufferProc() {
  matrix.selectFont(font5x7);
  memset(infoText[mosSeq], '\0', 128);
  strcpy(infoText[mosSeq], NAMA_MASJID);
  strcat(infoText[mosSeq], "\0");
  topPixLimit[mosSeq] = matrix.countPixelChar(infoText[mosSeq]);
  messageLenght[mosSeq] = matrix.totalChar;

  memset(infoText[jumatMes], '\0', 128);
  strcpy(infoText[jumatMes], TEXT_PESAN2);
  strcat(infoText[jumatMes], "\0");
  topPixLimit[jumatMes] = matrix.countPixelChar(infoText[jumatMes]);
  messageLenght[jumatMes] = matrix.totalChar;
}

void prayInfoBuffer() {
  matrix.selectFont(font5x7);
  memset(infoText[iqoSeq], '\0', 128);

  if (prayState == masukWaktu) {
    strcpy(infoText[iqoSeq], TEXT_IQOMAH);
    strcat(infoText[iqoSeq], "\0");
    topPixLimit[iqoSeq] = matrix.countPixelChar(infoText[iqoSeq]);
    messageLenght[iqoSeq] = matrix.totalChar;
  }

}
