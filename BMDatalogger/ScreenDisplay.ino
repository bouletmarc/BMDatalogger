void Display() {
  if (ScreenCurrentMenu == 2) {
    //Mil Menu
    ResetBufferIndex();
    GetInfosString(9);
    writeBigString(5, 0);
    GetMil();
  }
  else if (ScreenCurrentMenu >= 4 && ScreenCurrentMenu < 12) {
    DisplaySettingPage();
  }
  else if (ScreenCurrentMenu >= 13 && ScreenCurrentMenu <= 32) {
    DisplaySettingPageOption();
  }
  else if (ScreenCurrentMenu == 33) {
    DisplayOptionPage();
  }
  else {
    for (int i=0; i<8; i++) {
      ThisScreenIndex = 0;
      if (ScreenCurrentPage == 0) ScreenCurrentPage = 1;
      if (ScreenCurrentPage == 1) ThisScreenIndex = ScreenPage1[i];
      if (ScreenCurrentPage == 2) ThisScreenIndex = ScreenPage2[i];
      if (ScreenCurrentPage == 3) ThisScreenIndex = ScreenPage3[i];
      if (ScreenCurrentPage == 4) ThisScreenIndex = ScreenPage4[i];
      if (ScreenCurrentPage == 5) ThisScreenIndex = ScreenPage5[i];
      if (ScreenCurrentPage == 6) ThisScreenIndex = ScreenPage6[i];
      if (ScreenCurrentPage == 7) ThisScreenIndex = ScreenPage7[i];
      if (ScreenCurrentPage == 8) ThisScreenIndex = ScreenPage8[i];
  
      int ThisScreenMode = 0;                                 //normal
      if (ThisScreenIndex >= 100) ThisScreenMode = 1;         //progressbar
      if (ThisScreenIndex >= 200) ThisScreenMode = 2;         //big
      if (ThisScreenIndex >= 300) ThisScreenMode = 3;         //big2
      
      //peak values
      if (ScreenCurrentMenu == 1) {
        ThisScreenMode = 4;
        ThisScreenIndex = ScreenCurrentPeak;
      }

      //setting page menu '>' indicator
      if (ScreenCurrentMenu == 12) {
        SetCursor();
      }
      //####
      

      while (ThisScreenIndex >= 100) {
        ThisScreenIndex -= 100;
      }
      /*if (ThisScreenIndex >= 100) ThisScreenIndex -= 100;
      else if (ThisScreenIndex >= 200) ThisScreenIndex -= 200;
      else if (ThisScreenIndex >= 300) ThisScreenIndex -= 300;*/

      ResetBufferIndex();

      //Only Run 'reconized' data values
      if (ThisScreenIndex <= MaxDataValue) {
        GetSensorString(ThisScreenIndex);
        GetInfosString(39);
        
        if (ThisScreenMode < 2) {
          SetValueToBuffer();
          Add_Sensor_Desc();
        }
    
        SetPos(i);
        if (ThisScreenMode >= 1) XPos = 0;
        if (ThisScreenMode >= 3) YPos = 0;

        //normal
        if (ThisScreenMode == 0) {
          PrintText(10, XPos, YPos);
        }

        //progressbar
        if (ThisScreenMode == 1) {
          if (ProgressBarLeft == 0) XPos = 10;
          PrintText(10, XPos, YPos);
          if (ProgressBarLeft == 0) XPos = 0;
          if (ProgressBarLeft == 1) XPos = 10;
          DrawProgressBar((int) GetInt(), 10);
          i++;
        }

        //big font
        if (ThisScreenMode == 2) {
          PrintTextLenght(XPos, YPos);
          PrintTextLenghtEmpty(XPos, YPos + 1);
          int StartAt = GetBufferLenght();
          ResetBufferIndex();
          SetValueToBuffer();
          writeBigString(StartAt, YPos);
          i += 3;
        }

        //big font #2
        if (ThisScreenMode == 3) {
          writeBigString(XPos, YPos);
          ResetBufferIndex();
          SetValueToBuffer();
          writeBigString(XPos, YPos+2);
          i += 8;
        }

        //peak
        if (ThisScreenMode == 4) {
          writeBigString(XPos, YPos);
          ResetBufferIndex();
          GetInfosString(15);
          GetInfosString(39);
          Add_String(String(GetPeakMin()));
          Add_Sensor_Desc();
          PrintText(10, XPos, YPos + 2);

          ResetBufferIndex();
          GetInfosString(17);
          GetInfosString(39);
          SetValueToBuffer();
          Add_Sensor_Desc();
          PrintText(10, XPos + 10, YPos + 2);
          
          ResetBufferIndex();
          GetInfosString(16);
          GetInfosString(39);
          Add_String(String(GetPeakMax()));
          Add_Sensor_Desc();
          PrintText(20, XPos, YPos + 3);
          
          i += 8;
        }
      }
    }
  }
}

void SetPos(const int ThisLine) {
  XPos = 0;
  YPos = ThisLine;
    
  if (ThisLine == 1)  {
    XPos = 10;
    YPos = 0;
  }
  if (ThisLine == 2) YPos = 1;
  if (ThisLine == 3) {
    XPos = 10;
    YPos = 1;
  }
  if (ThisLine == 4) YPos = 2;
  if (ThisLine == 5) {
    XPos = 10;
    YPos = 2;
  }
  if (ThisLine == 6) YPos = 3;
  if (ThisLine == 7) {
    XPos = 10;
    YPos = 3;
  }
}

double GetInt() {
  if (ThisScreenIndex == 0) return (double) GetRpm();
  if (ThisScreenIndex == 1) return (double) GetEct();
  if (ThisScreenIndex == 2) return (double) GetIat();
  if (ThisScreenIndex == 3) return (double) GetTps();
  if (ThisScreenIndex == 4) return (double) GetO2();
  if (ThisScreenIndex == 5) return (double) GetIgn();
  if (ThisScreenIndex == 6) return (double) GetInjDurr();
  if (ThisScreenIndex == 7) return (double) GetInstantConsumption();
  if (ThisScreenIndex == 8) return (double) GetIACVDuty();
  if (ThisScreenIndex == 9) return (double) GetMap();
  if (ThisScreenIndex == 10) return (double) GetBoost();
  if (ThisScreenIndex == 11) return (double) GetVss();
  if (ThisScreenIndex == 12) return (double) GetSensorsActived(39, 6);
  if (ThisScreenIndex == 13) return (double) GetBattery();
  if (ThisScreenIndex == 14) return (double) GetSensorsActived(8, 2);
  if (ThisScreenIndex == 15) return (double) GetSensorsActived(8, 4);
  if (ThisScreenIndex == 16) return (double) GetInjFV();
  if (ThisScreenIndex == 17) return (double) GetSensorsActived(39, 5);
  if (ThisScreenIndex == 18) return (double) GetSpeedTime();
  if (ThisScreenIndex == 19) return (double) GetBestSpeedTime();
  if (ThisScreenIndex == 20) return (double) GetSensorsActived(23, 7);
  if (ThisScreenIndex == 21) return (double) GetSensorsActived(21, 3);
  if (ThisScreenIndex == 22) return (double) GetELDVolt();
  if (ThisScreenIndex == 23) return (double) GetSensorsActived(23, 6);
  if (ThisScreenIndex == 24) return (double) GetSensorsActived(22, 7);
  if (ThisScreenIndex == 25) return (double) GetSensorsActived(22, 5);
  if (ThisScreenIndex == 26) return (double) GetGear();

  if (ThisScreenIndex == 27) return (double) GetSensorsActived(39, 7);
  if (ThisScreenIndex == 28) return (double) GetSensorsActived(39, 0);
  if (ThisScreenIndex == 29) return (double) GetSensorsActived(39, 1);
  if (ThisScreenIndex == 30) return (double) GetSensorsActived(39, 2);
  if (ThisScreenIndex == 31) return (double) GetSensorsActived(39, 4);
  if (ThisScreenIndex == 32) return (double) GetSensorsActived(39, 3);
  if (ThisScreenIndex == 33) return (double) GetSensorsActived(43, 7);
  if (ThisScreenIndex == 34) return (double) GetSensorsActived(21, 0);
  if (ThisScreenIndex == 35) return (double) GetSensorsActived(21, 1);
  if (ThisScreenIndex == 36) return (double) GetSensorsActived(21, 2);
  if (ThisScreenIndex == 37) return (double) GetSensorsActived(21, 4);
  if (ThisScreenIndex == 38) return (double) GetSensorsActived(21, 5);
  if (ThisScreenIndex == 39) return (double) GetSensorsActived(8, 5);
  if (ThisScreenIndex == 40) return (double) GetSensorsActived(21, 7);
  if (ThisScreenIndex == 41) return (double) GetSensorsActived(22, 0);
  if (ThisScreenIndex == 42) return (double) GetSensorsActived(22, 2);
  if (ThisScreenIndex == 43) return (double) GetSensorsActived(22, 6);
  if (ThisScreenIndex == 44) return (double) GetSensorsActived(43, 0);
  if (ThisScreenIndex == 45) return (double) GetSensorsActived(43, 1);
  if (ThisScreenIndex == 46) return (double) GetSensorsActived(43, 2);
  if (ThisScreenIndex == 47) return (double) GetSensorsActived(43, 3);
  if (ThisScreenIndex == 48) return (double) GetSensorsActived(43, 4);
  if (ThisScreenIndex == 49) return (double) GetSensorsActived(43, 5);
  
  if (ThisScreenIndex == 50) return (double) GetSensorsActived(8, 0);
  if (ThisScreenIndex == 51) return (double) GetSensorsActived(8, 1);
  if (ThisScreenIndex == 52) return (double) GetSensorsActived(8, 3);
  if (ThisScreenIndex == 53) return (double) GetSensorsActived(8, 6);
  if (ThisScreenIndex == 54) return (double) GetSensorsActived(8, 7);
  if (ThisScreenIndex == 55) return (double) GetSensorsActived(21, 6);
  if (ThisScreenIndex == 56) return (double) GetSensorsActived(22, 4);
  if (ThisScreenIndex == 57) return (double) GetSensorsActived(23, 5);
  if (ThisScreenIndex == 58) return (double) GetSensorsActived(43, 6);
  if (ThisScreenIndex == 59) return (double) GetIgnTable();
  
  if (ThisScreenIndex == 60) return (double) GetSensorsActived(38, 0);
  if (ThisScreenIndex == 61) return (double) GetSensorsActived(38, 1);
  if (ThisScreenIndex == 62) return (double) GetSensorsActived(38, 2);
  if (ThisScreenIndex == 63) return (double) GetSensorsActived(38, 3);
  if (ThisScreenIndex == 64) return (double) GetSensorsActived(38, 4);
  if (ThisScreenIndex == 65) return (double) GetSensorsActived(38, 5);
  if (ThisScreenIndex == 66) return (double) GetSensorsActived(38, 6);
  if (ThisScreenIndex == 67) return (double) GetSensorsActived(38, 7);
  if (ThisScreenIndex == 68) return (double) GetBaro();
  if (ThisScreenIndex == 69) return (double) GetDuty();
  if (ThisScreenIndex == 70) return (double) GetECTFC();
  if (ThisScreenIndex == 71) return (double) GetO2Short();
  if (ThisScreenIndex == 72) return (double) GetO2Long();
  if (ThisScreenIndex == 73) return (double) GetIATFC();
  if (ThisScreenIndex == 74) return (double) GetVEFC();
  if (ThisScreenIndex == 75) return (double) GetIATIC();
  if (ThisScreenIndex == 76) return (double) GetECTIC();
  if (ThisScreenIndex == 77) return (double) GetGEARIC();
  if (ThisScreenIndex == 78) return (double) GetEBCBaseDuty();
  if (ThisScreenIndex == 79) return (double) GetEBCDuty();
}

void SetValueToBuffer() {
  if (ThisScreenIndex == 4 || ThisScreenIndex == 5 || ThisScreenIndex == 6 || ThisScreenIndex == 7
   || ThisScreenIndex == 10 || ThisScreenIndex == 13 || ThisScreenIndex == 16 || ThisScreenIndex == 18
   || ThisScreenIndex == 19 || ThisScreenIndex == 22 || ThisScreenIndex == 59 || ThisScreenIndex == 69
   || ThisScreenIndex == 70 || ThisScreenIndex == 71 || ThisScreenIndex == 72 || ThisScreenIndex == 73
   || ThisScreenIndex == 74 || ThisScreenIndex == 75 || ThisScreenIndex == 76 || ThisScreenIndex == 77
   || ThisScreenIndex == 78 || ThisScreenIndex == 79)
  {
    Add_String(String(GetInt()));
  }
  else Add_String(String((int) GetInt()));

  //remake double into 1decimal
  if (ThisScreenIndex == 4) RemoveLastChar();
  if (ThisScreenIndex == 7) RemoveLastChar();
  if (ThisScreenIndex == 10) RemoveLastChar();
  if (ThisScreenIndex == 13) RemoveLastChar();
  if (ThisScreenIndex == 18) RemoveLastChar();
  if (ThisScreenIndex == 19) RemoveLastChar();
}
