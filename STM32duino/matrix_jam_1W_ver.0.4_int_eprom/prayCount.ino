/*
 * source: https://github.com/cahyadsn/adzan
 * 
 */
int N, N2, N3;
float tt, tn, M, L, RA, RA1, Lquadrant, RAquadrant, sinDec, cosDec, cosH,
      zenith, H, T, UT, localT, decl, za, zd, x;

void countShalat() {
  unsigned char Month;
  int Year, jam, menit;

  Year = 1900 + waktu->tm_year;
  Month = waktu->tm_mon;
  Day = waktu->tm_mday;

  zenith = cos((110 * M_PI) / 180);
  N2 = (int) floor((Month + 10) / 12);
  N3 = (int) (1 + floor((Year - 4 * floor(Year / 4) + 2) / 3));
  N = (int) (floor(275 * (Month + 1) / 9)) - (N2 * N3) + Day - 30;

  tt = N + ((5 - (Longitude / 15)) / 24); // terbit
  M = (0.9856 * tt) - 3.289;
  L = M + (1.916 * sin((M * M_PI) / 180))
      + (0.020 * sin((2 * M * M_PI) / 180)) + 282.634;
  if (L > 360)
    L = L - 360;
  else if (L < 0)
    L = L + 360;
  RA1 = tan((L * M_PI) / 180);
  RA = atan(0.91764 * RA1) * (180 / M_PI);
  if (RA > 360)
    RA = RA - 360;

  Lquadrant = (floor(L / 90)) * 90;
  RAquadrant = (floor(RA / 90)) * 90;
  RA = RA + (Lquadrant - RAquadrant);
  RA = RA / 15;

  sinDec = 0.39782 * sin((L * M_PI) / 180);
  cosDec = cos(((asin(sinDec) * (180 / M_PI)) * M_PI) / 180);

  /**************************************************************************/

  cosH = (zenith - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (360 - (acos(cosH) * (180 / M_PI))) / 15;
  //    Htn = (acos(cosH) * (180 / M_PI)) / 15;

  T = (H + RA - (0.06571 * tt) - 6.622) + 0.01667; //Bandung
  //  T = (H + RA - (0.06571 * tt) - 6.622) + 0.0333; //Kediri

  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);

  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  sub_tstamp = (jam * 3600) + (menit * 60);
  iqoSubTimeout =  sub_tstamp + (iqoSub * 60);

  buff_subuh[0] = (jam / 10) + 48;
  buff_subuh[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_subuh[2] = ':';
  buff_subuh[3] = (menit / 10) + 48;
  buff_subuh[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/

  cosH = (cos((91.7 * M_PI) / 180)
          - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (360 - (acos(cosH) * (180 / M_PI))) / 15;

  T = H + RA - (0.06571 * tt) - 6.622;

  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  syu_tstamp = (jam * 3600) + (menit * 60);

  buff_syuruq[0] = (jam / 10) + 48;
  buff_syuruq[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_syuruq[2] = ':';
  buff_syuruq[3] = (menit / 10) + 48;
  buff_syuruq[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/

  cosH = (cos((85.2 * M_PI) / 180)
          - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (360 - (acos(cosH) * (180 / M_PI))) / 15;

  T = H + RA - (0.06571 * tt) - 6.622;

  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  dhu_tstamp = (jam * 3600) + (menit * 60);
  //  close_dhuTime = dhu_tstamp - preShola;
  buff_dhuha[0] = (jam / 10) + 48;
  buff_dhuha[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_dhuha[2] = ':';
  buff_dhuha[3] = (menit / 10) + 48;
  buff_dhuha[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/

  T = (RA - (0.06571 * tt) - 6.622) + 0.0333;
  //T = (RA - (0.06571 * tt) - 6.622) + 0.05;

  UT = T - (Longitude / 15);
  localT = (UT + 7);
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  dzu_tstamp = (jam * 3600) + (menit * 60);
  iqoDzuTimeout =  dzu_tstamp + (iqoDzu * 60);

  buff_dzuhur[0] = (jam / 10) + 48;
  buff_dzuhur[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_dzuhur[2] = ':';
  buff_dzuhur[3] = (menit / 10) + 48;
  buff_dzuhur[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/

  decl = asin(sinDec) * (180 / M_PI);
  zd = fabs(Latitude - decl);
  za = atan(1 + tan((zd * M_PI) / 180)) * (180 / M_PI);

  cosH = (cos((za * M_PI) / 180)
          - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (acos(cosH) * (180 / M_PI)) / 15;

  //      T = H + RA - (0.06571 * tt) - 6.622 + 0.01667;
  T = H + RA - (0.06571 * tt) - 6.622 + 0.03333;

  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  ash_tstamp = (jam * 3600) + (menit * 60);
  iqoAshTimeout =  ash_tstamp + (iqoAsh * 60);

  buff_ashar[0] = (jam / 10) + 48;
  buff_ashar[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_ashar[2] = ':';
  buff_ashar[3] = (menit / 10) + 48;
  buff_ashar[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/


  cosH = (cos((90.8333 * M_PI) / 180)
          - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (acos(cosH) * (180 / M_PI)) / 15;

  //  T = H + RA - (0.06571 * tt) - 6.622 + 0.03333; //Kediri
  T = H + RA - (0.06571 * tt) - 6.622 + 0.06666; //Bandung
  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  mag_tstamp = (jam * 3600) + (menit * 60);
  iqoMagTimeout =  mag_tstamp + (iqoMag * 60);

  buff_maghrib[0] = (jam / 10) + 48;
  buff_maghrib[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_maghrib[2] = ':';
  buff_maghrib[3] = (menit / 10) + 48;
  buff_maghrib[4] = (menit % ((menit / 10) * 10)) + 48;
  /**************************************************************************/

  cosH = (cos((108 * M_PI) / 180)
          - (sinDec * sin((Latitude * M_PI) / 180)))
         / (cosDec * cos((Latitude * M_PI) / 180));
  H = (acos(cosH) * (180 / M_PI)) / 15;

  T = H + RA - (0.06571 * tt) - 6.622 + 0.0333;

  UT = T - (Longitude / 15);
  localT = UT + 7;
  if (localT > 24)
    localT = localT - 24;
  else if (localT < 0)
    localT = localT + 24;
  x = fmod(localT, 1.0);
  jam = localT - x;
  x = x * 60;
  if (x > 0.5)
    menit = ceil(x);
  else if (x <= 0.5)
    menit = floor(x);
  if (menit >= 60) {
    menit = 0;
    jam += 1;
  }
  isy_tstamp = (jam * 3600) + (menit * 60);
  iqoIsyTimeout =  isy_tstamp + (iqoIsy * 60);

  buff_isya[0] = (jam / 10) + 48;
  buff_isya[1] = (jam % ((jam / 10) * 10)) + 48;
  buff_isya[2] = ':';
  buff_isya[3] = (menit / 10) + 48;
  buff_isya[4] = (menit % ((menit / 10) * 10)) + 48;
}
