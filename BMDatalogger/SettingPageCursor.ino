//int Showing = 0;
unsigned long last_shown_time=0;
const int SpawnTimeout = 600;

void SetCursor() {
  //Showing++;
  //if (Showing > 40) Showing = 0;
  //if (Showing <= 15) {
  if (millis() - last_shown_time > SpawnTimeout) {
    StringBuffer[0] = '>';
    if (ScreenSettingSelected == 0) {
      PrintText(1, 0, 0);
      StringBuffer[0] = '<';
      PrintText(1, 9, 0);
    }
    if (ScreenSettingSelected == 1) {
      PrintText(1, 10, 0);
      StringBuffer[0] = '<';
      PrintText(1, 19, 0);
    }
    if (ScreenSettingSelected == 2) {
      PrintText(1, 0, 0);
      StringBuffer[0] = '<';
      PrintText(1, 19, 0);
    }
    //########################################
    if (ScreenSettingSelected == 3) {
      PrintText(1, 0, 1);
      StringBuffer[0] = '<';
      PrintText(1, 9, 1);
    }
    if (ScreenSettingSelected == 4) {
      PrintText(1, 10, 1);
      StringBuffer[0] = '<';
      PrintText(1, 19, 1);
    }
    if (ScreenSettingSelected == 5) {
      PrintText(1, 0, 1);
      StringBuffer[0] = '<';
      PrintText(1, 19, 1);
    }
    if (ScreenSettingSelected == 6) {
      PrintText(1, 0, 0);
      StringBuffer[0] = '<';
      PrintText(1, 19, 1);
    }
    //########################################
    if (ScreenSettingSelected == 7) {
      PrintText(1, 0, 2);
      StringBuffer[0] = '<';
      PrintText(1, 9, 2);
    }
    if (ScreenSettingSelected == 8) {
      PrintText(1, 10, 2);
      StringBuffer[0] = '<';
      PrintText(1, 19, 2);
    }
    if (ScreenSettingSelected == 9) {
      PrintText(1, 0, 2);
      StringBuffer[0] = '<';
      PrintText(1, 19, 2);
    }
    if (ScreenSettingSelected == 10) {
      PrintText(1, 0, 1);
      StringBuffer[0] = '<';
      PrintText(1, 19, 2);
    }
    //########################################
    if (ScreenSettingSelected == 11) {
      PrintText(1, 0, 3);
      StringBuffer[0] = '<';
      PrintText(1, 9, 3);
    }
    if (ScreenSettingSelected == 12) {
      PrintText(1, 10, 3);
      StringBuffer[0] = '<';
      PrintText(1, 19, 3);
    }
    if (ScreenSettingSelected == 13) {
      PrintText(1, 0, 3);
      StringBuffer[0] = '<';
      PrintText(1, 19, 3);
    }
    if (ScreenSettingSelected == 14) {
      PrintText(1, 0, 2);
      StringBuffer[0] = '<';
      PrintText(1, 19, 3);
    }
    if (ScreenSettingSelected == 15) {
      PrintText(1, 0, 0);
      StringBuffer[0] = '<';
      PrintText(1, 19, 3);
    }

    if (millis() - last_shown_time > (SpawnTimeout * 2)) last_shown_time = millis();
  }
}

void IncreaseScreenIndex() {
  //ScreenSettingSelected
  //ScreenCurrentPage

  int ThisPageeeIndex = 0;
  if (ScreenSettingSelected == 1) ThisPageeeIndex = 1;
  if (ScreenSettingSelected == 2) ThisPageeeIndex = 0;
  
  if (ScreenSettingSelected == 3) ThisPageeeIndex = 2;
  if (ScreenSettingSelected == 4) ThisPageeeIndex = 3;
  if (ScreenSettingSelected == 5) ThisPageeeIndex = 2;
  if (ScreenSettingSelected == 6) ThisPageeeIndex = 0;
  
  if (ScreenSettingSelected == 7) ThisPageeeIndex = 4;
  if (ScreenSettingSelected == 8) ThisPageeeIndex = 5;
  if (ScreenSettingSelected == 9) ThisPageeeIndex = 4;
  if (ScreenSettingSelected == 10) ThisPageeeIndex = 2;
  
  if (ScreenSettingSelected == 11) ThisPageeeIndex = 6;
  if (ScreenSettingSelected == 12) ThisPageeeIndex = 7;
  if (ScreenSettingSelected == 13) ThisPageeeIndex = 6;
  if (ScreenSettingSelected == 14) ThisPageeeIndex = 4;
  if (ScreenSettingSelected == 15) ThisPageeeIndex = 0;

  int ThisScreenIndex = GetScreenIndex(ThisPageeeIndex);

  int ThisScreenMode = 0;                                 //normal
  if (ThisScreenIndex >= 100) ThisScreenMode = 1;         //progressbar
  if (ThisScreenIndex >= 200) ThisScreenMode = 2;         //big
  if (ThisScreenIndex >= 300) ThisScreenMode = 3;         //big2

  int ThisScreenModeSuposed = 0;
  if (ScreenSettingSelected == 2 || ScreenSettingSelected == 5 || ScreenSettingSelected == 9 || ScreenSettingSelected == 13) ThisScreenModeSuposed = 1;
  if (ScreenSettingSelected == 6 || ScreenSettingSelected == 10 || ScreenSettingSelected == 14) ThisScreenModeSuposed = 2;
  if (ScreenSettingSelected == 15) ThisScreenModeSuposed = 3;

  //put to index to '0-MaxSensors' Range
  ThisScreenIndex = ReRangeIndex(ThisScreenIndex);

  //increase by 1
  if (ThisScreenMode == ThisScreenModeSuposed) {
    ThisScreenIndex++;
    if (ThisScreenIndex >= MaxDataValue) ThisScreenIndex = 0;
  }

  //set proper index
  if (ThisScreenModeSuposed == 1) ThisScreenIndex = ThisScreenIndex + 100;
  if (ThisScreenModeSuposed == 2) ThisScreenIndex = ThisScreenIndex + 200;
  if (ThisScreenModeSuposed == 3) ThisScreenIndex = ThisScreenIndex + 300;

  //set index
  SetScreenIndex(ThisPageeeIndex, ThisScreenIndex);

  if (ThisScreenModeSuposed == 1) ReRangeScreenIndexMode(ThisPageeeIndex + 1); //SetScreenIndex(ThisPageeeIndex + 1, 0);
  if (ThisScreenModeSuposed == 2) {
    for (int i = 0; i < 3; i++) {
      ReRangeScreenIndexMode(ThisPageeeIndex + 1 + i);  //SetScreenIndex(ThisPageeeIndex + 1, 0);
    }
  }
  if (ThisScreenModeSuposed == 3) {
    for (int i = 0; i < 7; i++) {
      ReRangeScreenIndexMode(ThisPageeeIndex + 1 + i);  //SetScreenIndex(ThisPageeeIndex + 1, 0);
    }
  }

  //super big font remover
  if (ThisScreenModeSuposed != 3 && HasSuperBigFont()) ReRangeScreenIndexMode(0);

  //progbar remover
  if (ThisPageeeIndex == 1 || ThisPageeeIndex == 3 || ThisPageeeIndex == 5 || ThisPageeeIndex == 7) {
    if (ThisScreenModeSuposed != 1 && HasProgBarAt(ThisPageeeIndex - 1)) {
      ReRangeScreenIndexMode(ThisPageeeIndex - 1);
    }
  }
  
  if (ThisScreenModeSuposed == 2 && HasProgBar()) {
    for (int i = 0; i < 8; i++) {
      if (HasProgBarAt(i)) {
        ReRangeScreenIndexMode(i);
      }
    }
  }

  //big font remover
  if (ThisScreenModeSuposed != 2) {
    if (((ThisPageeeIndex == 1 || ThisPageeeIndex == 2 || ThisPageeeIndex == 3) && HasBigFontAt(0))
      || ((ThisPageeeIndex == 3 || ThisPageeeIndex == 4 || ThisPageeeIndex == 5) && HasBigFontAt(2))
      || ((ThisPageeeIndex == 5 || ThisPageeeIndex == 6 || ThisPageeeIndex == 7) && HasBigFontAt(4))) {
      
      if (ThisPageeeIndex == 1 || ThisPageeeIndex == 2 || ThisPageeeIndex == 3) ReRangeScreenIndexMode(0);
      if (ThisPageeeIndex == 3 || ThisPageeeIndex == 4 || ThisPageeeIndex == 5) ReRangeScreenIndexMode(2);
      if (ThisPageeeIndex == 5 || ThisPageeeIndex == 6 || ThisPageeeIndex == 7) ReRangeScreenIndexMode(4);
    }
  }

  if (ThisScreenModeSuposed == 1 && HasBigFont()) {
    for (int i = 0; i < 8; i++) {
      if (HasBigFontAt(i)) {
        ReRangeScreenIndexMode(i);
      }
    }
  }
}

bool HasProgBar() {
  bool HasProgBarPage = false;
  for (int i = 0; i < 8; i++) {
    if (HasProgBarAt(i)) {
      HasProgBarPage = true;
      i = 8;
    }
  }
  return HasProgBarPage;
}

bool HasProgBarAt(int ThisPageeeIndex) {
  bool HasProgBarPage = false;
  int TestIndex = GetScreenIndex(ThisPageeeIndex);
  if (TestIndex >= 100 && TestIndex < 200) HasProgBarPage = true;
  return HasProgBarPage;
}

bool HasBigFont() {
  bool HasBigFontPage = false;
  for (int i = 0; i < 8; i++) {
    if (HasBigFontAt(i)) {
      HasBigFontPage = true;
      i = 8;
    }
  }
  return HasBigFontPage;
}

bool HasBigFontAt(int ThisPageeeIndex) {
  bool HasBigFontPage = false;
  int TestIndex = GetScreenIndex(ThisPageeeIndex);
  if (TestIndex >= 200 && TestIndex < 300) HasBigFontPage = true;
  return HasBigFontPage;
}

bool HasSuperBigFont() {
  bool HasBigFontPage = false;
  int TestIndex = GetScreenIndex(0);
  if (TestIndex >= 300 && TestIndex < 400) {
    HasBigFontPage = true;
  }
  return HasBigFontPage;
}

void SetScreenIndex(int ThisPageeeIndex, int ThisScreenIndex) {
  if (ScreenCurrentPage == 0) ScreenCurrentPage = 1;
  if (ScreenCurrentPage == 1) ScreenPage1[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 2) ScreenPage2[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 3) ScreenPage3[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 4) ScreenPage4[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 5) ScreenPage5[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 6) ScreenPage6[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 7) ScreenPage7[ThisPageeeIndex] = ThisScreenIndex;
  if (ScreenCurrentPage == 8) ScreenPage8[ThisPageeeIndex] = ThisScreenIndex;
}

int GetScreenIndex(int ThisPageeeIndex) {
  int ThisScreenIndex = 0;
  if (ScreenCurrentPage == 0) ScreenCurrentPage = 1;
  if (ScreenCurrentPage == 1) ThisScreenIndex = ScreenPage1[ThisPageeeIndex];
  if (ScreenCurrentPage == 2) ThisScreenIndex = ScreenPage2[ThisPageeeIndex];
  if (ScreenCurrentPage == 3) ThisScreenIndex = ScreenPage3[ThisPageeeIndex];
  if (ScreenCurrentPage == 4) ThisScreenIndex = ScreenPage4[ThisPageeeIndex];
  if (ScreenCurrentPage == 5) ThisScreenIndex = ScreenPage5[ThisPageeeIndex];
  if (ScreenCurrentPage == 6) ThisScreenIndex = ScreenPage6[ThisPageeeIndex];
  if (ScreenCurrentPage == 7) ThisScreenIndex = ScreenPage7[ThisPageeeIndex];
  if (ScreenCurrentPage == 8) ThisScreenIndex = ScreenPage8[ThisPageeeIndex];

  return ThisScreenIndex;
}

int ReRangeIndex(int ThisScreenIndex) {
  //put to index to '0-MaxSensors' Range
  while (ThisScreenIndex >= 100) {
    ThisScreenIndex -= 100;
  }
  return ThisScreenIndex;
}

void ReRangeScreenIndexMode(int ThisPageeeIndex) {
  int ThisScreenIndex = GetScreenIndex(ThisPageeeIndex);
  ThisScreenIndex = ReRangeIndex(ThisScreenIndex);
  SetScreenIndex(ThisPageeeIndex, ThisScreenIndex);
}
