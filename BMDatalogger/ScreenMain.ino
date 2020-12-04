void ScreenMain(){
  ResetBufferIndex();
  GetInfosString(6);
  writeBigString(3, 0);
  
  if (ScreenCurrentMenu >= 0 && ScreenCurrentMenu < 4) {
    ResetBufferIndex();
    GetInfosString(7);
    PrintText(9, 1, 2);
  
    ResetBufferIndex();
    GetInfosString(8);
    PrintText(9, 11, 2);
    
    ResetBufferIndex();
    GetInfosString(25);
    PrintText(9, 1, 3);
  
    ResetBufferIndex();
    GetInfosString(22);
    PrintText(9, 11, 3);
  }
  else if (ScreenCurrentMenu >= 4 && ScreenCurrentMenu < 8) {
    ResetBufferIndex();
    GetInfosString(24);
    PrintText(9, 1, 2);
    
    ResetBufferIndex();
    GetInfosString(46);
    PrintText(9, 11, 2);
    
    ResetBufferIndex();
    PrintText(9, 1, 3);
    PrintText(9, 11, 3);
  }

  //reset empty indicator
  ResetBufferIndex();
  if (ScreenCurrentMenu != 0 && ScreenCurrentMenu != 4) PrintText(1, 0, 2);
  if (ScreenCurrentMenu != 1 && ScreenCurrentMenu != 5) PrintText(1, 10, 2);
  if (ScreenCurrentMenu != 2) PrintText(1, 0, 3);
  if (ScreenCurrentMenu != 3) PrintText(1, 10, 3);

  //Set Indicator
  StringBuffer[0] = '>';
  if (ScreenCurrentMenu == 0 || ScreenCurrentMenu == 4) PrintText(1, 0, 2);
  if (ScreenCurrentMenu == 1 || ScreenCurrentMenu == 5) PrintText(1, 10, 2);
  if (ScreenCurrentMenu == 2) PrintText(1, 0, 3);
  if (ScreenCurrentMenu == 3) PrintText(1, 10, 3);
}
