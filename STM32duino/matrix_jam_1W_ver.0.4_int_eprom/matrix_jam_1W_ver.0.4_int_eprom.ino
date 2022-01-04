/*
  بسم الله الرحمن الرحيم *
*/

// peer waktu sholat jumat

//#include <DMDv1_3.h>
#include <HUB08.h>
#include "RTClock.h"
#include <fonts/font5x7.h>
#include <fonts/LinLibertine32.h>
#include <EEPROM.h>

#define USART Serial3
/////////////////////////////////// Inisiasi DMD pin ////////////////////////////////////
///
///
///
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD matrix(DISPLAYS_ACROSS, DISPLAYS_DOWN);
RTClock rt(RTCSEL_LSE);

/**************************************** Begin Declaration ***************************************/

//////////////// Coordinate Variable//////////////////
//float Longitude = 108.443667, Latitude = -6.660453; //Cirebon
//float Longitude = 107.561833, Latitude = -6.931706; //Bandung
//float Longitude = 111.978716, Latitude = -7.801222; //Kediri
float Longitude, Latitude;
/////////////////////////////////////////// Clock /////////////////////////////////////////////////
///
///

#define LatAddr  10
#define LongAddr 26
#define SubAddr  42 
#define DzuAddr  43 
#define AshAddr  44 
#define MagAddr  45 
#define IsyAddr  46 
#define BrgAddr  47 
#define SpdAddr  48 
#define MjdAddr  50 

/////////////////////////////////// Inisiasi Buzzer pin ////////////////////////////////////
///
///

#define buzz_pin PA0
//#define ind_pin PC13
#define wifiPowPin PB1

#define pinBuzz 0x0001
#define Buzz(BIT)      (BIT) ? (GPIOA->regs->BSRR = pinBuzz)   : (GPIOA->regs->BRR = pinBuzz)

uint16_t buzzTone[4] = {0x03, 0x33, 0x9993, 0x3f};
bool buzzStat = false;
int elapsedBuzz = 0;
uint8_t Tone = 0;

bool offlineFlag = false;
int offlineCount = 420;   // hitungan modul wifi dimatikan (dalam detik)
int closePrayTime = 180;  //2 x 60s  waktu menjelang sholat  (dalam detik)
int jumatTime = 1200, closeJumat = 300; //1200; //20 x 60   (dalam detik) 1200 300
const uint8_t jedaWaktuSholat = 6; //tampilan save mode saat sholat (dalam menit)
//////////////////////////////////////// RTC ////////////////////////////////////////////////
///
///
///

struct tm * waktu;
time_t ssec;
uint32_t WIB = 25200, epoch;
unsigned char Day;
int cur_tstamp;

int sub_tstamp, syu_tstamp, dhu_tstamp, dzu_tstamp, ash_tstamp, mag_tstamp, isy_tstamp;

//////////////////////////////////////  Flag Waktu Sholat ////////////////////////////////////////////////
///
///
///


int8_t iqoSub, iqoDzu, iqoAsh, iqoMag, iqoIsy;
int iqoSubTimeout, iqoDzuTimeout, iqoAshTimeout, iqoMagTimeout, iqoIsyTimeout;
//bool inTime = false;

//bool sholaTimeFlag = false;
typedef enum shola {
  idle = 0, subuh, syuruq, dhuha, dzuhur, ashar, maghrib, isya
};
shola sholat = idle;
typedef enum statusSholat {
  luarWaktu = 0, masukWaktu, dalamWaktu
};
statusSholat prayState, tmpPrayState;


uint8_t tmp_jam, tmp_menit;
int tock;
bool flick = false;
bool clearMain = false;
bool saveMode = false;

////////////////////////////// Menu Variable ///////////////////////////////////
///
///
///

//bool mainDisplay = true;
bool mainMenu = true;
uint8_t brightVal, textSpeed;
char latBuff[16], longBuff[16];
//////////////////////////////////Buffer Processing /////////////////////////////////////
//
//
String inputString;
char timeBuff[16];  // YYYYMMDDHHmmSS

///////////////////////////////// Display variable ///////////////////////////////////////
///
///
///

typedef enum diplayTopSeq {
  praySeq = 0, dateSeq, mosSeq, iqoSeq, flickSeq, jumatMes
};
int startSlowPix = 0, endSlowPix = 0;
bool drawBotFlag = false, drawTopFlag = false , drawMenu = false, clearTop = false;//,  drawLeftFlag = true; //clearAll = false,
diplayTopSeq topRowSeq = mosSeq;
int topCursorX;
int randX, randY;
int topPixLimit[7];
int topShiftPixel[7] = {64, 64, 64, 64, 64, 64};
uint8_t messageLenght[6], mesDuration[6] = {6, 8, 8, 7, 9, 8};
char infoText[6][128];
char outputChar[32];

char NAMA_MASJID[128] = "Masjid Al Hidayah, Lemah Hegar Kiaracondong - Bandung";
#define TEXT_IQOMAH   "Iqomah"
//char TEXT_PESAN1[128] = "Rapat dan luruskan shaf karena rapat dan lurus shaf termasuk dari kesempurnaan sholat";
#define TEXT_PESAN2   "Mohon non-aktifkan handphone di dalam masjid. Dilarang berbicara saat khotib berkhutbah"

/************************************************** End of Declaration ***********************************************/


void setup() {
  bool checkUID = false;
  //  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

  pinMode(wifiPowPin, OUTPUT);
  digitalWrite(wifiPowPin, HIGH);
  delay(100);
  digitalWrite(wifiPowPin, LOW);
  pinMode(buzz_pin, OUTPUT);
  USART.begin(115200);

  EEPROM.PageBase0 = 0x801F000;
  EEPROM.PageBase1 = 0x801F800;
  EEPROM.PageSize  = 0x200;
  EEPROM.init();

  delay(50);
  loadRom();
  if ((brightVal < 1) || (brightVal > 20)) {
    brightVal = 6;
    EEPROM.write(BrgAddr, (uint16_t) brightVal);
  }
  if ((textSpeed < 1) || (textSpeed > 20)) {
    textSpeed = 14;
    EEPROM.write(SpdAddr, (uint16_t) textSpeed);
  }
  //  checkUID = decrypt();
  //  while (!checkUID) {
  //    wR1(1);
  //    wD(1);
  //    wCLK(1);
  //    wCLK(0);
  //  }

  mesDuration[mosSeq] = 22 - textSpeed;
  mesDuration[dateSeq] = 22 - textSpeed;
  mesDuration[praySeq] = 22 - textSpeed;
  mesDuration[jumatMes] = 22 - textSpeed;
  ssec = WIB + rt.getTime();
  if (ssec < 1553037557) {
    rt.setTime(1553037557);
    ssec = 1553037557;
  }
  waktu = localtime (&ssec);

  countShalat();
  Timer2.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  Timer2.setPeriod(20); // in microseconds
  Timer2.setCompare1(1);      // overflow might be small
  Timer2.attachCompare1Interrupt(scanHandler);

  rt.attachSecondsInterrupt(tick);
  delay(500);
  matrix.clearScreen(true);

  drawBottom();
  topBufferProc();
  customBufferProc();
  enaBuzz(1, 0);
}

void loop() {
  switch (offlineFlag) {
    case false:
      if (USART.available() > 0) {
        Timer2.pause();
        // get the new byte:
        char inChar = (char) USART.read();
        if ((inChar >= 32) && (inChar < 127))
          inputString += inChar;
        if (inChar == '\n') {
          if (inputString.startsWith("T,") == true) {
            rt.detachSecondsInterrupt();
            inputString.remove(0, 2);
            inputString.toCharArray(timeBuff, sizeof(inputString));
            ssec = strtoul(timeBuff, NULL, 0);
            rt.setTime(ssec);
            clearMain = true;
            waktu = localtime (&ssec);

            checkPrayTime();
            drawBottom();
            prayInfoBuffer();
            customBufferProc();
            topBufferProc();
            enaBuzz(1, 0);
            //        USART.println(ssec);
            rt.attachSecondsInterrupt(tick);
          } else if (inputString.startsWith("I,") == true) {
            inputString.remove(0, 2);
            iqoSub = inputString.toInt();
            if (iqoSub > 25)iqoSub = 25;
            EEPROM.write(SubAddr, (uint16_t) iqoSub);
            inputString.remove(0, inputString.indexOf(',') + 1);

            iqoDzu = inputString.toInt();
            if (iqoDzu > 15)iqoDzu = 15;
            EEPROM.write( DzuAddr, (uint16_t) iqoDzu);
            inputString.remove(0, inputString.indexOf(',') + 1);

            iqoAsh = inputString.toInt();
            if (iqoAsh > 15)iqoAsh = 15;
            EEPROM.write(AshAddr, (uint16_t) iqoAsh);
            inputString.remove(0, inputString.indexOf(',') + 1);

            iqoMag = inputString.toInt();
            if (iqoMag > 15)iqoMag = 15;
            EEPROM.write(MagAddr, (uint16_t) iqoMag);
            inputString.remove(0, inputString.indexOf(',') + 1);

            iqoIsy = inputString.toInt();
            if (iqoIsy > 15)iqoIsy = 15;
            EEPROM.write(IsyAddr, (uint16_t) iqoIsy);
            prayInfoBuffer();
            enaBuzz(1, 0);
            //outBuff();
          } else if (inputString.startsWith("S,") == true) {
            inputString.remove(0, 2);
            textSpeed = inputString.toInt();
            mesDuration[mosSeq] = 22 - textSpeed;
            mesDuration[dateSeq] = 22 - textSpeed;
            mesDuration[praySeq] = 22 - textSpeed;
            EEPROM.write(SpdAddr,  (uint16_t) textSpeed);
            enaBuzz(1, 0);
            //            USART.println(textSpeed);
            //outBuff();
          } else if (inputString.startsWith("LL,") == true) {
            memset(latBuff, '\0', 16);
            inputString.remove(0, 3);
            inputString.toCharArray(latBuff, inputString.indexOf(',') + 1);
            Latitude = atof(latBuff);
            for (int idx = 0; idx < strlen(latBuff) ; idx++) {
              EEPROM.write(LatAddr + idx, (uint16_t) latBuff[idx]);
              USART.print(latBuff[idx]);
            }
//            USART.print("\nlat in buff: ");
//            USART.println(latBuff);
//            USART.print("lat in float: ");
//            USART.println(Latitude, 5);
            inputString.remove(0, inputString.indexOf(',') + 1);
            memset(longBuff, '\0', 16);
            inputString.toCharArray(longBuff, inputString.length() + 1);
            for (int idx = 0; idx < strlen(longBuff) ; idx++) {
              EEPROM.write(LongAddr + idx, (uint16_t) longBuff[idx]);
              USART.print(longBuff[idx]);
            }
            Longitude = atof(longBuff);
//            USART.print("\nlong in buff: ");
//            USART.println(longBuff);
//            USART.print("long in float: ");
//            USART.println(Longitude, 5);
            enaBuzz(1, 0);
            //outBuff();
          } else if (inputString.startsWith("MJ,") == true) {
            inputString.remove(0, 3);
            memset(NAMA_MASJID, '\0', 80);
            inputString.toCharArray(NAMA_MASJID, inputString.length() + 1);
            for (int idx = 0; idx < 80 ; idx++) {
              EEPROM.write(MjdAddr + idx, (uint16_t) NAMA_MASJID[idx]);
            }
//            USART.print("masjid: ");
//            USART.println(NAMA_MASJID);
            enaBuzz(1, 0);
          } else if (inputString.startsWith("WOFF") == true) {
            //            digitalWrite(wifiPowPin, HIGH);
          } else if (inputString.startsWith("B,") == true) {
            inputString.remove(0, 2);
            brightVal = inputString.toInt();
            EEPROM.write(BrgAddr,  (uint16_t) brightVal);
            enaBuzz(1, 0);
            //            USART.println(brightVal);

          } else if (inputString.startsWith("reboot") == true) {
            nvic_sys_reset();
          } else if (inputString.startsWith("load") == true) {
            loadRom();
          } else if (inputString.startsWith("?") == true) {
          }
          inputString = "";
        }
        Timer2.refresh();
        Timer2.resume();
      }
      break;
  }

  if (clearMain) {
    clearMain = false;
    matrix.clearScreen(true);
  }

  if (drawBotFlag) {
    drawBotFlag = false;
    dateBuff();
    drawBottom();
  }
  if (!saveMode) {
    if (drawTopFlag) {
      drawTopFlag = false;
      drawTop();
    }
  }
}

void tick() {
  switch (offlineFlag) {
    case false:
      offlineCount--;
      OBLed(1);
      if (offlineCount <= 0) {
        offlineFlag = true;
        digitalWrite(wifiPowPin, HIGH);
      }
      break;
  }

  flick = true;
  ssec = WIB + rt.getTime();
  waktu = localtime (&ssec);
  cur_tstamp = (int)(ssec % 86400);

  if (Day != waktu->tm_mday) {
    countShalat();
    topBufferProc();
    customBufferProc();
  }
  if (tmp_jam != (uint8_t) waktu->tm_hour) {
    hourToBuff();
  } else if (tmp_menit != (uint8_t) waktu->tm_min) {
    if (saveMode) {
      randX = random(0, 34);
      randY = random(0, 25);
      clearMain = true;
    }
    minToBuff();
  }
  drawBotFlag = true;

  tmp_jam = (uint8_t) waktu->tm_hour;
  tmp_menit = (uint8_t) waktu->tm_min;
  //  if (sholat != idle) {
  checkPrayTime();

  //  }
  //  USART.println("tick");
}
