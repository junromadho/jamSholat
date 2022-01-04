
void checkPrayTime() {
  static shola tmpWaktuSholat;
  if ((cur_tstamp <= sub_tstamp + ((iqoSub + jedaWaktuSholat) * 60) + 1) && (cur_tstamp >= sub_tstamp - closePrayTime)) {
    sholat = subuh;
  }  else if ((cur_tstamp <= syu_tstamp + 2) && (cur_tstamp >= syu_tstamp - closePrayTime)) {
    sholat = syuruq;
  } else if ((cur_tstamp <= dhu_tstamp + 2) && (cur_tstamp >= dhu_tstamp - closePrayTime)) {
    sholat = dhuha;
  } else if ((waktu->tm_wday != 5) && ((cur_tstamp <= dzu_tstamp + ((iqoDzu + jedaWaktuSholat) * 60) + 1) && (cur_tstamp >= dzu_tstamp - closePrayTime))) {
    sholat = dzuhur;
  } else if ((waktu->tm_wday == 5) && ((cur_tstamp <= dzu_tstamp + jumatTime) && (cur_tstamp >= dzu_tstamp - closeJumat))) {  //600
    sholat = dzuhur;
  } else if ((cur_tstamp <= ash_tstamp + ((iqoAsh + jedaWaktuSholat) * 60) + 1) && (cur_tstamp >= ash_tstamp - closePrayTime)) {
    sholat = ashar;
  } else if ((cur_tstamp <= mag_tstamp + ((iqoMag + jedaWaktuSholat) * 60) + 1) && (cur_tstamp >= mag_tstamp - closePrayTime)) {
    sholat = maghrib;
  } else if ((cur_tstamp <= isy_tstamp + ((iqoIsy + jedaWaktuSholat) * 60) + 1) && (cur_tstamp >= isy_tstamp - closePrayTime)) {
    sholat = isya;
  } else if ((cur_tstamp >= 75600 ) || (cur_tstamp <= 10800)) {
    if (!saveMode) {
      clearMain = true;
      saveMode = true;
    }
  } else {
    if (saveMode) {
      clearMain = true;
      saveMode = false;
    }
    sholat = idle;
  }

  if (sholat != idle) {
    switch (sholat) {
      case subuh:
        if ((cur_tstamp >= sub_tstamp) && (cur_tstamp < sub_tstamp + (iqoSub * 60))) {
          prayState = masukWaktu;
        } else if ((cur_tstamp >= sub_tstamp + (iqoSub * 60)) && (cur_tstamp < sub_tstamp + ((iqoSub + jedaWaktuSholat) * 60))) {
          prayState = dalamWaktu;
        }  else if (cur_tstamp >= sub_tstamp + ((iqoSub + jedaWaktuSholat) * 60)) {
          prayState = luarWaktu;
        }
        break;
      case syuruq:
        if (cur_tstamp >= syu_tstamp) {
          prayState = luarWaktu;
        }
        break;
      case dhuha:
        if (cur_tstamp >= dhu_tstamp) {
          prayState = luarWaktu;
        }
        break;
      case dzuhur:
        if (waktu->tm_wday != 5) {
          if ((cur_tstamp >= dzu_tstamp) && (cur_tstamp < dzu_tstamp + (iqoDzu * 60))) {
            prayState = masukWaktu;
          } else if ((cur_tstamp >= dzu_tstamp + (iqoDzu * 60)) && (cur_tstamp < dzu_tstamp + ((iqoDzu + jedaWaktuSholat) * 60))) {
            prayState = dalamWaktu;
          }  else if (cur_tstamp >= dzu_tstamp + ((iqoDzu + jedaWaktuSholat) * 60)) {
            prayState = luarWaktu;
          }
        } else {
          if ((cur_tstamp >= dzu_tstamp) && (cur_tstamp < dzu_tstamp + 180)) {
            prayState = masukWaktu;
          } else if ((cur_tstamp >= dzu_tstamp + 180) && (cur_tstamp < dzu_tstamp + jumatTime)) {   //20 menit x 60
            prayState = dalamWaktu;
          }  else if (cur_tstamp >= dzu_tstamp + jumatTime) {
            prayState = luarWaktu;
          }
        }
        break;
      case ashar:
        if ((cur_tstamp >= ash_tstamp) && (cur_tstamp < ash_tstamp + (iqoAsh * 60))) {
          prayState = masukWaktu;
        } else if ((cur_tstamp >= ash_tstamp + (iqoAsh * 60)) && (cur_tstamp < ash_tstamp + ((iqoAsh + jedaWaktuSholat) * 60))) {
          prayState = dalamWaktu;
        }  else if (cur_tstamp >= ash_tstamp + ((iqoAsh + jedaWaktuSholat) * 60)) {
          prayState = luarWaktu;
        }

        break;
      case maghrib:
        if ((cur_tstamp >= mag_tstamp) && (cur_tstamp < mag_tstamp + (iqoMag * 60))) {
          prayState = masukWaktu;
        } else if ((cur_tstamp >= mag_tstamp + (iqoMag * 60)) && (cur_tstamp < mag_tstamp + ((iqoMag + jedaWaktuSholat) * 60))) {
          prayState = dalamWaktu;
        }  else if (cur_tstamp >= mag_tstamp + ((iqoMag + jedaWaktuSholat) * 60)) {
          prayState = luarWaktu;
        }

        break;
      case isya:
        if ((cur_tstamp >= isy_tstamp) && (cur_tstamp < isy_tstamp + (iqoIsy * 60))) {
          prayState = masukWaktu;
        } else if ((cur_tstamp >= isy_tstamp + (iqoIsy * 60)) && (cur_tstamp < isy_tstamp + ((iqoIsy + jedaWaktuSholat) * 60))) {
          prayState = dalamWaktu;
        }  else if (cur_tstamp >= isy_tstamp + ((iqoIsy + jedaWaktuSholat) * 60)) {
          prayState = luarWaktu;
        }

        break;
    }

    if (tmpPrayState != prayState) {
      clearMain = true;
      if (prayState == masukWaktu) {
        enaBuzz(5, 1);
      } else if (prayState == dalamWaktu) {
        if ((waktu->tm_wday == 5) && (sholat == dzuhur)) {
        } else {
          enaBuzz(3, 3);
          mesDuration[praySeq] = 22 - textSpeed;
        }
      } else if (prayState == luarWaktu) {
        mesDuration[praySeq] = 22 - textSpeed;
      }
    }
    //    topRowSeq = praySeq;
    topBufferProc();
    prayInfoBuffer();
    tmpPrayState = prayState;
  }

  if (tmpWaktuSholat != sholat) {
    if (tmpWaktuSholat == idle) {
      enaBuzz(1, 0);
      topBufferProc();
    } else if ((tmpWaktuSholat == syuruq) || (tmpWaktuSholat == dhuha)) {
      enaBuzz(2, 3);
    }  else {

      clearMain = true;
    }
  }
  tmpWaktuSholat = sholat;
}
