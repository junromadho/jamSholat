
void enaBuzz(int jeda, uint8_t nada) {
  Tone = nada;
  elapsedBuzz = jeda;
  buzzStat = true;
}

void scanHandler() {
  //  static int flag0Tick = 0;
  static uint8_t Bit;
  static uint16_t buzzTick;
  static int topShiftInc, virPwm = 22;
  int ring;
  //  checkRot();
  virPwm--;
  if (virPwm == 21) {
    matrix.scanDisplay(true);
  } else if (virPwm == brightVal) {
    matrix.scanDisplay(false);
  } else if (virPwm < 0) {
    virPwm = 22;
  }

  if (flick) {
    tock++;
    if (tock >= 25000) {
      OBLed(0);
      flick = false;
      drawBotFlag = true;
      tock = 0;
    }
  }

  switch (saveMode) {
    case false:
      if (prayState != masukWaktu) {
        if (matrix.endRow) {
          /*if ((topRowSeq == praySeq) && (sholat != idle)) {
            if ((topShiftPixel[topRowSeq] <= (39 - startSlowPix)) && (topShiftPixel[topRowSeq] >= (25 - endSlowPix))) {
              mesDuration[topRowSeq] = 12;
            }
            else
              mesDuration[topRowSeq] = 22 - textSpeed;;
            }*/
          topShiftInc++;
          if (topShiftInc > mesDuration[topRowSeq] ) {
            drawTopFlag = true;
            topShiftPixel[topRowSeq]--;
            if (topShiftPixel[topRowSeq] < (1 - topPixLimit[topRowSeq])) {
              if (sholat == idle) {
                if (topRowSeq == praySeq)
                  topRowSeq = dateSeq;
                else if (topRowSeq == dateSeq) {
                  topRowSeq = mosSeq;
                } else if (topRowSeq == mosSeq)
                  topRowSeq = praySeq;
                topShiftPixel[topRowSeq] = 64;
              }  else if ((sholat == dzuhur) && (waktu->tm_wday == 5)) {

                if (topRowSeq == praySeq) {
                  topRowSeq = dateSeq;
                } else if (topRowSeq == dateSeq) {
                  topRowSeq = jumatMes;
                } else if (topRowSeq == jumatMes) {
                  topRowSeq = praySeq;
                } else if (topRowSeq == mosSeq) {
                  topRowSeq = jumatMes;
                }
                topShiftPixel[topRowSeq] = 64;
              } else {
                if (topRowSeq == praySeq)
                  topRowSeq = dateSeq;
                else if (topRowSeq == dateSeq)
                  if (prayState == masukWaktu)
                    topRowSeq = iqoSeq;
                  else
                    topRowSeq = praySeq;
                else if (topRowSeq == iqoSeq)
                  if (prayState != masukWaktu)
                    topRowSeq = iqoSeq;
                  else
                    topRowSeq = praySeq;
                else if (topRowSeq == mosSeq)
                  topRowSeq = praySeq;
                topShiftPixel[topRowSeq] = 64;
              }
            }
            topShiftInc = 0;
          }
          matrix.endRow = false;
        }
      } else if (prayState == masukWaktu) {
        if ((waktu->tm_wday == 5) && (sholat == dzuhur)) {
          if (matrix.endRow) {
            topShiftInc++;
            if (topShiftInc > mesDuration[topRowSeq] ) {
              drawTopFlag = true;
              topShiftPixel[topRowSeq]--;
              if (topShiftPixel[topRowSeq] < (1 - topPixLimit[topRowSeq])) {

                if (topRowSeq == praySeq) {
                  topRowSeq = dateSeq;
                } else if (topRowSeq == dateSeq) {
                  topRowSeq = jumatMes;
                } else if (topRowSeq == jumatMes) {
                  topRowSeq = praySeq;
                } else if (topRowSeq == mosSeq) {
                  topRowSeq = jumatMes;
                }
                topShiftPixel[topRowSeq] = 64;

              }
              topShiftInc = 0;
            }
            matrix.endRow = false;
          }
        } else {
          drawTopFlag = true;
        }
      } else {
        drawTopFlag = true;
      }

      break;
    case true:

      break;
  }
  if (buzzStat) {
    buzzTick++;
    if (buzzTick > 3500) {
      buzzTick = 0;
      Buzz((buzzTone[Tone] >> Bit) & 0x01);
      Bit++;
      if (Bit > 16) {
        Bit = 0;
        elapsedBuzz--;
        if (elapsedBuzz <= 0) {
          Bit = 0;
          buzzStat = false;
          buzzTick = 0;
          Buzz(0);
        }
      }
    }
  }
}

void drawTop() {
  if (clearTop) {
    matrix.drawFilledBox(0, 0, 63, 11, GRAPHICS_INVERSE);
    clearTop = false;
  }

  if (!saveMode) {
    matrix.selectFont(font5x7);

    if (prayState == luarWaktu) {
      if ((topRowSeq == praySeq) && (sholat != idle)) {
        if (flick) {
          matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[topRowSeq],  messageLenght[topRowSeq], GRAPHICS_NORMAL);
        } else {
          matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[flickSeq],  messageLenght[flickSeq], GRAPHICS_NORMAL);
        }
      } else {
        matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[topRowSeq],  messageLenght[topRowSeq], GRAPHICS_NORMAL);
      }
    } else if (prayState == masukWaktu) {
      if ((waktu->tm_wday == 5) && (sholat == dzuhur))  {
        //      matrix.drawString(topPixLimit[jumatMes], 0, infoText[jumatMes],  messageLenght[jumatMes], GRAPHICS_NORMAL);/
        if ((topRowSeq == praySeq) && (sholat != idle)) {
          if (flick) {
            matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[topRowSeq],  messageLenght[topRowSeq], GRAPHICS_NORMAL);
          } else {
            matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[flickSeq],  messageLenght[flickSeq], GRAPHICS_NORMAL);
          }
        } else {
          matrix.drawString(topShiftPixel[topRowSeq], 0, infoText[topRowSeq],  messageLenght[topRowSeq], GRAPHICS_NORMAL);
        }
      } else {
        matrix.selectFont(font5x7);
        matrix.drawString(32 - (topPixLimit[iqoSeq] / 2), 0, infoText[iqoSeq],  messageLenght[iqoSeq], GRAPHICS_NORMAL);
      }
    }
  } else {}
}

void drawBottom() {
  //  if (!saveMode) {
  if ((prayState == luarWaktu) && (!saveMode)) {
    matrix.selectFont(LinLibertine32);

    matrix.drawString(2, 11, buff_jam, 2, GRAPHICS_NORMAL);
    if (flick == true) {
      matrix.drawChar(30, 11, ':', GRAPHICS_NORMAL);
    } else {
      matrix.drawChar(30, 11, ';', GRAPHICS_NORMAL);
    }
    matrix.drawString(37, 11, buff_mnt, 2, GRAPHICS_NORMAL);

  } else if (prayState == masukWaktu) {
    if ((waktu->tm_wday == 5) && (sholat == dzuhur)) {
      matrix.selectFont(LinLibertine32);
      matrix.drawString(2, 11, buff_jam, 2, GRAPHICS_NORMAL);
      if (flick == true) {
        matrix.drawChar(30, 11, ':', GRAPHICS_NORMAL);
      } else {
        matrix.drawChar(30, 11, ';', GRAPHICS_NORMAL);
      }
      matrix.drawString(37, 11, buff_mnt, 2, GRAPHICS_NORMAL);

    } else {
      matrix.selectFont(LinLibertine32);
      iqomahBuff();
      matrix.drawString(2, 11, buff_iqoMnt, 2, GRAPHICS_NORMAL);
      matrix.drawChar(30, 11, ':', GRAPHICS_NORMAL);
      matrix.drawString(37, 11, buff_iqoDtk, 2, GRAPHICS_NORMAL);
    }
  } else {
    matrix.selectFont(font5x7);
    matrix.drawString(randX, randY, buff_jam, 2, GRAPHICS_NORMAL);
    if (flick == true) {
      matrix.drawChar(randX + 12, randY, ':', GRAPHICS_NORMAL);
    } else {
      matrix.drawChar(randX + 12, randY, '$', GRAPHICS_NORMAL);
    }
    matrix.drawString(randX + 17, randY, buff_mnt, 2, GRAPHICS_NORMAL);
  }
}
