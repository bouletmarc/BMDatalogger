unsigned long last_shown_option_time=0;
const int SpawnTimeoutOption = 1200;
int CurrentShowOption = 0;

void DisplayOptionPage() {
  if (millis() - last_shown_option_time > SpawnTimeoutOption) {
    CurrentShowOption++;
    if (CurrentShowOption > 3) CurrentShowOption = 0;
    last_shown_option_time = millis();
  }
  
  ResetBufferIndex();
  GetOptionString(ScreenSettingSelected);
  GetInfosString(39);
  PrintText(20, 0, 0);

  //###########################
  //Option Value
  ResetBufferIndex();
  if (ScreenSettingSelected == 13) {
    Add_String(String(Timeout));
    Add_String("ms");
  }
  if (ScreenSettingSelected == 14) {
    Add_String(String(Brightness));
    //int Percent = (Brightness * 100) / 255;
    //Add_String(String(Percent));
    //Add_String("%");
    NightMode = false;
    RefreshBackLight();
  }
  if (ScreenSettingSelected == 15) {
    Add_String(String((int) ProgressBarMode));
    XPos = 10;
    YPos = 1;
    DrawProgressBarPercent(50, 10);
  }
  if (ScreenSettingSelected == 16) {
    Add_String(String((int) ProgressBarLeft));
    if (ProgressBarLeft == 0) Add_String(" (right)");
    if (ProgressBarLeft == 1) Add_String(" (left)");
  }
  if (ScreenSettingSelected == 17) {
    Add_String(String(Injectors_Size));
    Add_String("cc");
  }
  if (ScreenSettingSelected == 18) {
    Add_String(String((int) O2Input));
    if (O2Input == 0) Add_String(" (O2)");
    if (O2Input == 1) Add_String(" (EGR)");
    if (O2Input == 2) Add_String(" (ELD)");
    if (O2Input == 3) Add_String(" (B6)");
  }
  if (ScreenSettingSelected == 19) {
    Add_String(String((int) UseCelcius));
    Add_String(" (");
    GetTempCelcius();
    Add_String(")");
  }
  if (ScreenSettingSelected == 20) {
    Add_String(String((int) UseKMH));
    if (UseKMH == 0) Add_String(" (mph)");
    if (UseKMH == 1) Add_String(" (kmh)");
  }
  if (ScreenSettingSelected == 21) {
    Add_String(String((int) O2Type));
    if (O2Type == 0) Add_String(" (AFR)");
    if (O2Type == 1) Add_String(" (Lambda)");
    if (O2Type == 2) Add_String(" (Voltage)");
  }
  if (ScreenSettingSelected == 22) {
    Add_String(String((int) Warning_RPM));
    Add_String("rpm");
  }
  if (ScreenSettingSelected == 23) {
    Add_String(String((int) Warning_ECT));
    GetTempCelcius();
  }
  if (ScreenSettingSelected == 24) {
    Add_String(String((int) Warning_IAT));
    GetTempCelcius();
  }
  if (ScreenSettingSelected == 25) {
    Add_String(String((int) mBarMin));
    Add_String("mBar");
  }
  if (ScreenSettingSelected == 26) {
    Add_String(String((int) mBarMax));
    Add_String("mBar");
  }
  if (ScreenSettingSelected == 27) {
    Add_String(String((int) TempMin));
    GetTempCelcius();
  }
  if (ScreenSettingSelected == 28) {
    Add_String(String((int) TempMax));
    GetTempCelcius();
  }
  if (ScreenSettingSelected == 29) {
    if (CurrentShowOption == 0) {
      Add_String("Volt:");
      Add_String(String((double) WBConversion[0]) + "/" + String((double) WBConversion[2]));
    }
    if (CurrentShowOption == 1) {
      Add_String("Lambda:");
      Add_String(String((double) WBConversion[1]) + "/" + String((double) WBConversion[3]));
    }
    if (CurrentShowOption == 2) {
      Add_String("AFR:");
      Add_String(String((double) (WBConversion[1] * 14.7)) + "/" + String((double) (WBConversion[3] * 14.7)));
    }
    if (CurrentShowOption == 3) {
      Add_String("Sensor:");
      if (WBModel == 0) Add_String("OEM");
      if (WBModel == 1) Add_String("AEM");
      if (WBModel == 2) Add_String("PLX-M");
      if (WBModel == 3) Add_String("FJO");
      if (WBModel == 4) Add_String("LC1/LM1");
      if (WBModel == 5) Add_String("Techedge");
      if (WBModel == 6) Add_String("Zeitronix");
      if (WBModel == 7) Add_String("Motec PLM");
      if (WBModel == 8) Add_String("JAW");
      //if (WBModel == 9) Add_String("Custom");
    }
  }
  if (ScreenSettingSelected == 30) {
    if (CurrentShowOption == 0) {
      long Value = (((long) MapByte[1] * 256) + (long) MapByte[0]) - 32768;
      Add_String("mBar Min:" + String(Value));
    }
    if (CurrentShowOption == 1) {
      long Value = (((long) MapByte[3] * 256) + (long) MapByte[2]) - 32768;
      Add_String("mBar Max:" + String(Value));
    }
    if (CurrentShowOption == 2 || CurrentShowOption == 3) {
      Add_String("Sensor:");
      if (MapModel == 0) Add_String("OEM");
      if (MapModel == 1) Add_String("GM 2");
      if (MapModel == 2) Add_String("GM 3");
      if (MapModel == 3) Add_String("Motorola 2.5");
      if (MapModel == 4) Add_String("AEM 3.5");
      if (MapModel == 5) Add_String("Xenocron 3");
      if (MapModel == 6) Add_String("Xenocron 4");
      if (MapModel == 7) Add_String("AEM 5");
      if (MapModel == 8) Add_String("Omni/Hondata4");
    }
  }
  if (ScreenSettingSelected == 31) {
    if (CurrentShowOption == 0) {
      Add_String("Gear1-2:");
      Add_String(String((int) Tranny[0]) + "/" + String((int) Tranny[1]));
    }
    if (CurrentShowOption == 1) {
      Add_String("Gear2-3:");
      Add_String(String((int) Tranny[1]) + "/" + String((int) Tranny[2]));
    }
    if (CurrentShowOption == 2) {
      Add_String("Gear3-4:");
      Add_String(String((int) Tranny[2]) + "/" + String((int) Tranny[3]));
    }
    if (CurrentShowOption == 3) {
      Add_String("Box:");
      if (TrannyModel == 0) Add_String("Y21/Y80/S80 EDM");
      if (TrannyModel == 1) Add_String("ITR S80 JDM96-97");
      if (TrannyModel == 2) Add_String("ITR S80 JDM98-01");
      if (TrannyModel == 3) Add_String("ITR S80 USDM97+");
      if (TrannyModel == 4) Add_String("Z6/Y8");
      if (TrannyModel == 5) Add_String("GSR USDM 94+");
      if (TrannyModel == 6) Add_String("GSR JDM 93+ SIR");
      if (TrannyModel == 7) Add_String("LS/RS/GS/SE 94+");
      if (TrannyModel == 8) Add_String("H22 USDM 92-96");
      if (TrannyModel == 9) Add_String("H22 JDM 92-96");
      if (TrannyModel == 10) Add_String("H23 USDM 92-96");
      if (TrannyModel == 11) Add_String("H23 JDM 92-96");
      if (TrannyModel == 12) Add_String("D16Y7");
    }
  }
  
  if (ScreenSettingSelected == 15) {
    PrintText(10, 0, 1);
  }
  else {
    PrintText(20, 0, 1);
  }
  //###########################
  
  ResetBufferIndex();
  GetInfosString(41);
  PrintText(9, 1, 2);
  
  ResetBufferIndex();
  GetInfosString(40);
  PrintText(9, 11, 2);
  
  ResetBufferIndex();
  GetInfosString(34);
  PrintText(19, 1, 3);
  
  //###########################
  //reset empty indicator
  ResetBufferIndex();
  if (ScreenOptionSelected != 0) PrintText(1, 0, 2);
  if (ScreenOptionSelected != 1) PrintText(1, 10, 2);
  if (ScreenOptionSelected != 2) PrintText(1, 0, 3);
  
  //Set Indicator
  StringBuffer[0] = '>';
  if (ScreenOptionSelected == 0) PrintText(1, 0, 2);
  if (ScreenOptionSelected == 1) PrintText(1, 10, 2);
  if (ScreenOptionSelected == 2) PrintText(1, 0, 3);
}

//####################################################################################################
//####################################################################################################
//####################################################################################################

void GetOptionString(int ThisOptionIndex) {
  //Timeout, backlight, Bar Type, Bar Side
  if (ThisOptionIndex == 13) {
    GetInfosString(27);
  }
  else if (ThisOptionIndex == 14) {
    GetInfosString(28);
  }
  else if (ThisOptionIndex == 15) {
    GetInfosString(29);
    AddThisChar(' ');
    GetInfosString(30);
  }
  else if (ThisOptionIndex == 16) {
    GetInfosString(29);
    AddThisChar(' ');
    GetInfosString(31);
  }
  //Inj_Size, O2_Input, Temp, Speed
  else if (ThisOptionIndex == 17) {
    GetInfosString(32);
    AddThisChar(' ');
    GetInfosString(33);
  }
  else if (ThisOptionIndex == 18) {
    GetSensorString(4);
    AddThisChar(' ');
    GetInfosString(35);
  }
  else if (ThisOptionIndex == 19) {
    GetInfosString(37);
  }
  else if (ThisOptionIndex == 20) {
    GetInfosString(38);
  }
  //O2 Type, Warning_Max_RPM, Warning_Max_ECT, Warning_Max_IAT
  else if (ThisOptionIndex == 21) {
    GetSensorString(4);
    AddThisChar(' ');
    GetInfosString(30);
  }
  else if (ThisOptionIndex == 22) {
    GetInfosString(16);
    AddThisChar(' ');
    GetSensorString(0);
  }
  else if (ThisOptionIndex == 23) {
    GetInfosString(16);
    AddThisChar(' ');
    GetSensorString(1);
  }
  else if (ThisOptionIndex == 24) {
    GetInfosString(16);
    AddThisChar(' ');
    GetSensorString(2);
  }
  //MAP_Min, MAP_Max, Temp_Min, Temp_Max
  else if (ThisOptionIndex == 25) {
    GetInfosString(15);
    AddThisChar(' ');
    GetSensorString(9);
  }
  else if (ThisOptionIndex == 26) {
    GetInfosString(16);
    AddThisChar(' ');
    GetSensorString(9);
  }
  else if (ThisOptionIndex == 27) {
    GetInfosString(15);
    AddThisChar(' ');
    GetInfosString(37);
  }
  else if (ThisOptionIndex == 28) {
    GetInfosString(16);
    AddThisChar(' ');
    GetInfosString(37);
  }
  //WBConversion, MapByte, Tranny
  else if (ThisOptionIndex == 29) {
    GetInfosString(42);
    AddThisChar(' ');
    GetInfosString(43);
  }
  else if (ThisOptionIndex == 30) {
    GetSensorString(9);
    AddThisChar(' ');
    GetInfosString(43);
  }
  else if (ThisOptionIndex == 31) {
    GetInfosString(44);
    GetInfosString(43);
  }
}

//####################################################################################################
//####################################################################################################
//####################################################################################################

void DecreaseOption() {
  CurrentShowOption = 3;
  last_shown_option_time = millis();
  
  if (ScreenSettingSelected == 13) {
    Timeout -= 25;
    if (Timeout < 50) Timeout = 600;
  }
  if (ScreenSettingSelected == 14) {
    if (Brightness == 255) Brightness = 250;
    Brightness -= 25;
    if (Brightness < 0) Brightness = 255;
    RefreshBackLight();
  }
  if (ScreenSettingSelected == 15) {
    ProgressBarMode -= 1;
    if (ProgressBarMode < 0 || ProgressBarMode > 6) ProgressBarMode = 6;
  }
  if (ScreenSettingSelected == 16) {
    ProgressBarLeft -= 1;
    if (ProgressBarLeft < 0 || ProgressBarLeft > 1) ProgressBarLeft = 1;
  }
  if (ScreenSettingSelected == 17) {
    Injectors_Size -= 10;
    if (Injectors_Size < 180) Injectors_Size = 2000;
  }
  if (ScreenSettingSelected == 18) {
    O2Input -= 1;
    if (O2Input < 0 || O2Input > 3) O2Input = 3;
  }
  if (ScreenSettingSelected == 19) {
    UseCelcius -= 1;
    if (UseCelcius < 0 || UseCelcius > 1) UseCelcius = 1;
  }
  if (ScreenSettingSelected == 20) {
    UseKMH -= 1;
    if (UseKMH < 0 || UseKMH > 1) UseKMH = 1;
  }
  if (ScreenSettingSelected == 21) {
    O2Type -= 1;
    if (O2Type < 0 || O2Type > 2) O2Type = 2;
  }
  if (ScreenSettingSelected == 22) {
    Warning_RPM -= 50;
    if (Warning_RPM < 5000) Warning_RPM = 11000;
  }
  if (ScreenSettingSelected == 23) {
    if (UseCelcius == 0) {
      Warning_ECT -= 5;
      if (Warning_ECT < -40) Warning_ECT = 290;
    }
    else {
      Warning_ECT -= 1;
      if (Warning_ECT < -40) Warning_ECT = 141;
    }
  }
  if (ScreenSettingSelected == 24) {
    if (UseCelcius == 0) {
      Warning_IAT -= 5;
      if (Warning_IAT < -40) Warning_IAT = 290;
    }
    else {
      Warning_IAT -= 1;
      if (Warning_IAT < -40) Warning_IAT = 141;
    }
  }
  if (ScreenSettingSelected == 25) {
    mBarMin -= 10;
    if (mBarMin < -70) mBarMin = 250;
  }
  if (ScreenSettingSelected == 26) {
    if (mBarMax == 1790) mBarMax = 1800;
    mBarMax -= 100;
    if (mBarMax < 1000) mBarMax = 5000;
    if (mBarMax == 1800) mBarMax = 1790;
  }
  if (ScreenSettingSelected == 27) {
    if (UseCelcius == 0) {
      TempMin -= 5;
      if (TempMin < -40) TempMin = 290;
    }
    else {
      TempMin -= 1;
      if (TempMin < -40) TempMin = 141;
    }
  }
  if (ScreenSettingSelected == 28) {
    if (UseCelcius == 0) {
      TempMax -= 5;
      if (TempMax < -40) TempMax = 290;
    }
    else {
      TempMax -= 1;
      if (TempMax < -40) TempMax = 141;
    }
  }
  if (ScreenSettingSelected == 29) {
    WBModel -= 1;
    if (WBModel < 0) WBModel = 8;
    SetWB();
  }
  if (ScreenSettingSelected == 30) {
    MapModel -= 1;
    if (MapModel < 0) MapModel = 8;
    SetMap();
  }
  if (ScreenSettingSelected == 31) {
    TrannyModel -= 1;
    if (TrannyModel < 0) TrannyModel = 12;
    SetTranny();
  }

  delay(40);
  //SetWait();
  last_shown_option_time = millis();
}

//####################################################################################################
//####################################################################################################
//####################################################################################################

void SetWB() {
  if (WBModel == 0) { WBConversion[0] = 0; WBConversion[1] = 1.3; WBConversion[2] = 1; WBConversion[3] = 0.71; }
  if (WBModel == 1) { WBConversion[0] = 0.5; WBConversion[1] = 0.75; WBConversion[2] = 3.38; WBConversion[3] = 1.14; }
  if (WBModel == 2) { WBConversion[0] = 0; WBConversion[1] = 0.68; WBConversion[2] = 5; WBConversion[3] = 1.36; }
  if (WBModel == 3) { WBConversion[0] = 0.85; WBConversion[1] = 0.68; WBConversion[2] = 5; WBConversion[3] = 1.36; }
  if (WBModel == 4) { WBConversion[0] = 0; WBConversion[1] = 0.51; WBConversion[2] = 5; WBConversion[3] = 1.52; }
  if (WBModel == 5) { WBConversion[0] = 0; WBConversion[1] = 0.61; WBConversion[2] = 5; WBConversion[3] = 1.29; }
  if (WBModel == 6) { WBConversion[0] = 0.15; WBConversion[1] = 0.65; WBConversion[2] = 3.47; WBConversion[3] = 1.51; }
  if (WBModel == 7) { WBConversion[0] = 1; WBConversion[1] = 0.73; WBConversion[2] = 4.5; WBConversion[3] = 1.5; }
  if (WBModel == 8) { WBConversion[0] = 1.02; WBConversion[1] = 0.69; WBConversion[2] = 2.21; WBConversion[3] = 1.5; }
}

void SetTranny() {
  if (TrannyModel == 0) { Tranny[0] = 0x46; Tranny[1] = 0x67; Tranny[2] = 0x8E; Tranny[3] = 0xB8; }
  if (TrannyModel == 1) { Tranny[0] = 0x46; Tranny[1] = 0x67; Tranny[2] = 0x8E; Tranny[3] = 0xB8; }
  if (TrannyModel == 2) { Tranny[0] = 0x42; Tranny[1] = 0x5D; Tranny[2] = 0x87; Tranny[3] = 0xB6; }
  if (TrannyModel == 3) { Tranny[0] = 0x46; Tranny[1] = 0x64; Tranny[2] = 0x91; Tranny[3] = 0xB8; }
  if (TrannyModel == 4) { Tranny[0] = 0x48; Tranny[1] = 0x71; Tranny[2] = 0xAA; Tranny[3] = 0xE3; }
  if (TrannyModel == 5) { Tranny[0] = 0x46; Tranny[1] = 0x6E; Tranny[2] = 0x9A; Tranny[3] = 0xC4; }
  if (TrannyModel == 6) { Tranny[0] = 0x46; Tranny[1] = 0x6E; Tranny[2] = 0x9A; Tranny[3] = 0xC4; }
  if (TrannyModel == 7) { Tranny[0] = 0x48; Tranny[1] = 0x71; Tranny[2] = 0xB2; Tranny[3] = 0xD6; }
  if (TrannyModel == 8) { Tranny[0] = 0x47; Tranny[1] = 0x6E; Tranny[2] = 0x9E; Tranny[3] = 0xC3; }
  if (TrannyModel == 9) { Tranny[0] = 0x47; Tranny[1] = 0x6E; Tranny[2] = 0x9E; Tranny[3] = 0xC9; }
  if (TrannyModel == 10) { Tranny[0] = 0x47; Tranny[1] = 0x6E; Tranny[2] = 0x9E; Tranny[3] = 0xC9; }
  if (TrannyModel == 11) { Tranny[0] = 0x4A; Tranny[1] = 0x7B; Tranny[2] = 0xAF; Tranny[3] = 0xE0; }
  if (TrannyModel == 12) { Tranny[0] = 0x4B; Tranny[1] = 0x7D; Tranny[2] = 0xBC; Tranny[3] = 0xED; }
}

void SetMap() {
  if (MapModel == 0) { MapByte[0] = 0xba; MapByte[1] = 0x7f; MapByte[2] = 0xfe; MapByte[3] = 0x86; }
  if (MapModel == 1) { MapByte[0] = 0x08; MapByte[1] = 0x80; MapByte[2] = 0xf9; MapByte[3] = 0x87; }
  if (MapModel == 2) { MapByte[0] = 0x0b; MapByte[1] = 0x80; MapByte[2] = 0x53; MapByte[3] = 0x8c; }
  if (MapModel == 3) { MapByte[0] = 0x46; MapByte[1] = 0x80; MapByte[2] = 0x1e; MapByte[3] = 0x8a; }
  if (MapModel == 4) { MapByte[0] = 0x51; MapByte[1] = 0x7e; MapByte[2] = 0x04; MapByte[3] = 0x8f; }
  if (MapModel == 5) { MapByte[0] = 0x0b; MapByte[1] = 0x80; MapByte[2] = 0xe0; MapByte[3] = 0x8b; }
  if (MapModel == 6) { MapByte[0] = 0x23; MapByte[1] = 0x80; MapByte[2] = 0x54; MapByte[3] = 0x90; }
  if (MapModel == 7) { MapByte[0] = 0x8f; MapByte[1] = 0x7d; MapByte[2] = 0xf9; MapByte[3] = 0x95; }
  if (MapModel == 8) { MapByte[0] = 0x23; MapByte[1] = 0x80; MapByte[2] = 0x54; MapByte[3] = 0x90; }

  mBarMin = (int) ((((long) MapByte[1] * 256) + (long) MapByte[0]) - 32768);
  mBarMax = (int) ((((long) MapByte[3] * 256) + (long) MapByte[2]) - 32768);
}

//####################################################################################################
//####################################################################################################
//####################################################################################################
void IncreaseOption() {
  CurrentShowOption = 3;
  last_shown_option_time = millis();
    
  if (ScreenSettingSelected == 13) {
    Timeout += 25;
    if (Timeout > 600) Timeout = 50;
  }
  if (ScreenSettingSelected == 14) {
    if (Brightness == 255) Brightness = 250;
    Brightness += 25;
    if (Brightness == 250) Brightness = 255;
    if (Brightness > 255) Brightness = 0;
    RefreshBackLight();
  }
  if (ScreenSettingSelected == 15) {
    ProgressBarMode += 1;
    if (ProgressBarMode > 6) ProgressBarMode = 0;
  }
  if (ScreenSettingSelected == 16) {
    ProgressBarLeft += 1;
    if (ProgressBarLeft > 1) ProgressBarLeft = 0;
  }
  if (ScreenSettingSelected == 17) {
    Injectors_Size += 10;
    if (Injectors_Size > 2000) Injectors_Size = 180;
  }
  if (ScreenSettingSelected == 18) {
    O2Input += 1;
    if (O2Input > 3) O2Input = 0;
  }
  if (ScreenSettingSelected == 19) {
    UseCelcius += 1;
    if (UseCelcius > 1) UseCelcius = 0;
  }
  if (ScreenSettingSelected == 20) {
    UseKMH += 1;
    if (UseKMH > 1) UseKMH = 0;
  }
  if (ScreenSettingSelected == 21) {
    O2Type += 1;
    if (O2Type > 2) O2Type = 0;
  }
  if (ScreenSettingSelected == 22) {
    Warning_RPM += 50;
    if (Warning_RPM > 11000) Warning_RPM = 5000;
  }
  if (ScreenSettingSelected == 23) {
    if (UseCelcius == 0) {
      Warning_ECT += 5;
      if (Warning_ECT > 190) Warning_ECT = -40;
    }
    else {
      Warning_ECT += 1;
      if (Warning_ECT > 141) Warning_ECT = -40;
    }
  }
  if (ScreenSettingSelected == 24) {
    if (UseCelcius == 0) {
      Warning_IAT += 5;
      if (Warning_IAT > 190) Warning_IAT = -40;
    }
    else {
      Warning_IAT += 1;
      if (Warning_IAT > 141) Warning_IAT = -40;
    }
  }
  if (ScreenSettingSelected == 25) {
    mBarMin += 10;
    if (mBarMin > 250) mBarMin = -70;
  }
  if (ScreenSettingSelected == 26) {
    if (mBarMax == 1790) mBarMax = 1800;
    mBarMax += 100;
    if (mBarMax > 5000) mBarMax = 1000;
    if (mBarMax == 1800) mBarMax = 1790;
  }
  if (ScreenSettingSelected == 27) {
    if (UseCelcius == 0) {
      TempMin += 5;
      if (TempMin > 290) TempMin = -40;
    }
    else {
      TempMin += 1;
      if (TempMin > 141) TempMin = -40;
    }
  }
  if (ScreenSettingSelected == 28) {
    if (UseCelcius == 0) {
      TempMax += 5;
      if (TempMax > 290) TempMax = -40;
    }
    else {
      TempMax += 1;
      if (TempMax > 141) TempMax = -40;
    }
  }
  if (ScreenSettingSelected == 29) {
    WBModel += 1;
    if (WBModel > 8) WBModel = 0;
    SetWB();
  }
  if (ScreenSettingSelected == 30) {
    MapModel += 1;
    if (MapModel > 8) MapModel = 0;
    SetMap();
  }
  if (ScreenSettingSelected == 31) {
    TrannyModel += 1;
    if (TrannyModel > 12) TrannyModel = 0;
    SetTranny();
  }
  
  delay(40);
  //SetWait();
  last_shown_option_time = millis();
}
