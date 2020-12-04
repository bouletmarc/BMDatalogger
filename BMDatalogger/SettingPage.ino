void DisplaySettingPage() {
  //Settings Menu
  ResetBufferIndex();
  PrintText(2, 0, 0);
  PrintText(2, 0, 1);
  PrintText(3, 17, 0);
  PrintText(3, 17, 1);
  GetInfosString(24);
  writeBigString(2, 0);
  //###########################
  ResetBufferIndex();
  GetInfosString(5);
  if (ScreenCurrentMenu < 8) Add_String("1");
  else Add_String("5");
  PrintText(9, 1, 2);

  ResetBufferIndex();
  GetInfosString(5);
  if (ScreenCurrentMenu < 8) Add_String("2");
  else Add_String("6");
  PrintText(9, 11, 2);
  
  ResetBufferIndex();
  GetInfosString(5);
  if (ScreenCurrentMenu < 8) Add_String("3");
  else Add_String("7");
  PrintText(9, 1, 3);

  ResetBufferIndex();
  GetInfosString(5);
  if (ScreenCurrentMenu < 8) Add_String("4");
  else Add_String("8");
  PrintText(9, 11, 3);

  //###########################
  //reset empty indicator
  ResetBufferIndex();
  if (ScreenCurrentMenu != 4 && ScreenCurrentMenu != 8) PrintText(1, 0, 2);
  if (ScreenCurrentMenu != 5 && ScreenCurrentMenu != 9) PrintText(1, 10, 2);
  if (ScreenCurrentMenu != 6 && ScreenCurrentMenu != 10) PrintText(1, 0, 3);
  if (ScreenCurrentMenu != 7 && ScreenCurrentMenu != 11) PrintText(1, 10, 3);

  //Set Indicator
  StringBuffer[0] = '>';
  if (ScreenCurrentMenu == 4 || ScreenCurrentMenu == 8) PrintText(1, 0, 2);
  if (ScreenCurrentMenu == 5 || ScreenCurrentMenu == 9) PrintText(1, 10, 2);
  if (ScreenCurrentMenu == 6 || ScreenCurrentMenu == 10) PrintText(1, 0, 3);
  if (ScreenCurrentMenu == 7 || ScreenCurrentMenu == 11) PrintText(1, 10, 3);
}

void DisplaySettingPageOption() {
    //AddThisChar(' ');
  //Settings Menu
  ResetBufferIndex();
  PrintText(2, 0, 0);
  PrintText(2, 0, 1);
  PrintText(3, 17, 0);
  PrintText(3, 17, 1);
  GetInfosString(24);
  writeBigString(2, 0);
  //###########################
  if (ScreenCurrentMenu >= 13 && ScreenCurrentMenu < 17) {
    //Timeout, backlight, Bar Type, Bar Side
    ResetBufferIndex();
    GetOptionString(13);
    PrintText(9, 1, 2);
    
    ResetBufferIndex();
    GetOptionString(14);
    PrintText(9, 11, 2);
    
    ResetBufferIndex();
    GetOptionString(15);
    PrintText(9, 1, 3);
    
    ResetBufferIndex();
    GetOptionString(16);
    PrintText(9, 11, 3);
  }
  else if (ScreenCurrentMenu >= 17 && ScreenCurrentMenu < 21) {
    //Inj_Size, O2_Input, Temp, Speed
    ResetBufferIndex();
    GetOptionString(17);
    PrintText(9, 1, 2);
    
    ResetBufferIndex();
    GetOptionString(18);
    PrintText(9, 11, 2);

    ResetBufferIndex();
    GetOptionString(19);
    PrintText(9, 1, 3);
    
    ResetBufferIndex();
    GetOptionString(20);
    PrintText(9, 11, 3);
  }
  else if (ScreenCurrentMenu >= 21 && ScreenCurrentMenu < 25) {
    //O2 Type, Warning_Max_RPM, Warning_Max_ECT, Warning_Max_IAT
    ResetBufferIndex();
    GetOptionString(21);
    PrintText(9, 1, 2);
    
    ResetBufferIndex();
    GetOptionString(22);
    PrintText(9, 11, 2);
    
    ResetBufferIndex();
    GetOptionString(23);
    PrintText(9, 1, 3);
    
    ResetBufferIndex();
    GetOptionString(24);
    PrintText(9, 11, 3);
  }
  else if (ScreenCurrentMenu >= 25 && ScreenCurrentMenu < 29) {
    //MAP_Min, MAP_Max, Temp_Min, Temp_Max
    ResetBufferIndex();
    GetOptionString(25);
    PrintText(9, 1, 2);
    
    ResetBufferIndex();
    GetOptionString(26);
    PrintText(9, 11, 2);

    ResetBufferIndex();
    GetOptionString(27);
    PrintText(9, 1, 3);
    
    ResetBufferIndex();
    GetOptionString(28);
    PrintText(9, 11, 3);
  }

  else if (ScreenCurrentMenu >= 29 && ScreenCurrentMenu < 33) {
    //WBConversion, MapByte, Tranny, Back
    ResetBufferIndex();
    GetOptionString(29);
    PrintText(9, 1, 2);

    ResetBufferIndex();
    GetOptionString(30);
    PrintText(9, 11, 2);

    ResetBufferIndex();
    GetOptionString(31);
    PrintText(9, 1, 3);

    //Back
    ResetBufferIndex();
    GetInfosString(34);
    PrintText(9, 11, 3);
  }

  //reset empty indicator
  ResetBufferIndex();
  if (ScreenCurrentMenu != 13 && ScreenCurrentMenu != 17 && ScreenCurrentMenu != 21 && ScreenCurrentMenu != 25 && ScreenCurrentMenu != 29) PrintText(1, 0, 2);
  if (ScreenCurrentMenu != 14 && ScreenCurrentMenu != 18 && ScreenCurrentMenu != 22 && ScreenCurrentMenu != 26 && ScreenCurrentMenu != 30) PrintText(1, 10, 2);
  if (ScreenCurrentMenu != 15 && ScreenCurrentMenu != 19 && ScreenCurrentMenu != 23 && ScreenCurrentMenu != 27 && ScreenCurrentMenu != 31) PrintText(1, 0, 3);
  if (ScreenCurrentMenu != 16 && ScreenCurrentMenu != 20 && ScreenCurrentMenu != 24 && ScreenCurrentMenu != 28 && ScreenCurrentMenu != 32) PrintText(1, 10, 3);

  //Set Indicator
  StringBuffer[0] = '>';
  if (ScreenCurrentMenu == 13 || ScreenCurrentMenu == 17 || ScreenCurrentMenu == 21 || ScreenCurrentMenu == 25 || ScreenCurrentMenu == 29) PrintText(1, 0, 2);
  if (ScreenCurrentMenu == 14 || ScreenCurrentMenu == 18 || ScreenCurrentMenu == 22 || ScreenCurrentMenu == 26 || ScreenCurrentMenu == 30) PrintText(1, 10, 2);
  if (ScreenCurrentMenu == 15 || ScreenCurrentMenu == 19 || ScreenCurrentMenu == 23 || ScreenCurrentMenu == 27 || ScreenCurrentMenu == 31) PrintText(1, 0, 3);
  if (ScreenCurrentMenu == 16 || ScreenCurrentMenu == 20 || ScreenCurrentMenu == 24 || ScreenCurrentMenu == 28 || ScreenCurrentMenu == 32) PrintText(1, 10, 3);
}
