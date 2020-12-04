#define ON 1
#define OFF 0
volatile int buttonBack = 0;
volatile int buttonNext = 0;
volatile int buttonDual = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 60;
volatile bool ButtonsPressed = false;
int BrightnessBuffer = 255;
int BrightnessBufferNight = 150;

void CheckButtons() {
  
  //###################
  //Atmega64A
  pin_ISR1();
  pin_ISR2();
  //###################
  
  if (ButtonsPressed) {
      if (millis() - last_interrupt_time > debouncing) {
        ButtonsPressed = false;
        last_interrupt_time = millis();
        GetButtonStates();
        
        buttonBack=OFF;
        buttonNext=OFF;
        buttonDual=OFF;
        
        //last_interrupt_time = millis();
      }
  }
}

void pin_ISR1()
{
  if (digitalRead(BackButton) == LOW) {
    buttonBack=ON;
    ButtonsPressed = true;
    ResetButtonTime();
  }
  CheckDualButton();
}

void pin_ISR2()
{
  if (digitalRead(NextButton) == LOW) {
    buttonNext=ON;
    ButtonsPressed = true;
    ResetButtonTime();
  }
  CheckDualButton();
}

void CheckDualButton() {
  if (digitalRead(NextButton) == LOW && digitalRead(BackButton) == LOW) {
    buttonBack=OFF;
    buttonNext=OFF;
    buttonDual=ON;
    ButtonsPressed = true;
    ResetButtonTime();
  }

  //ResetButtonTime();
}

void ResetButtonTime() {
  last_interrupt_time = millis();
  WaitingQuick = true;
  WaitingDelay = debouncing*2;
}

void GetButtonStates() {
  if (buttonBack == ON) {
    /*if (ShowJ12) {
      BypassJ12();
    }
    else {*/
      if (!InMain) {
        if (ScreenCurrentMenu >= 4 && ScreenCurrentMenu < 12) {
          SettingMenuNext();
        }
        else if (ScreenCurrentMenu >= 13 && ScreenCurrentMenu <= 32) {
          SettingMenuNext();
        }
        else if (ScreenCurrentMenu == 32) {
          MainMenu();
        }
        else if (ScreenCurrentMenu == 33) {
          OptionMenuNext();
        }
        else if (ScreenCurrentMenu == 12) {
          SettingPageNext();
        }
        else {
          MainMenu(); //Return to Main Menu
        }
      } else {
        if (!Sleeping) {
          MainMenuNext();
        }
        else {
          SleepDevice(); //disable sleeping
        }
      }
    //}
    
    //AutoSaveEEPROM();
  }
  
  if (buttonNext == ON) {
    /*if (ShowJ12) {
      BypassJ12();
    }
    else {*/
      if (!InMain) {
        if (ScreenCurrentMenu >= 4) {
          if (ScreenCurrentMenu >= 4 && ScreenCurrentMenu < 12) {
            SettingMenu(1);
          }
          else if (ScreenCurrentMenu >= 13 && ScreenCurrentMenu < 32) {
            SettingMenu(2);
          }
          else if (ScreenCurrentMenu == 12) {
            IncreaseScreenIndex();
          }
          else if (ScreenCurrentMenu == 32) {
            MainMenu();
          }
          else if (ScreenCurrentMenu == 33) {
            if (ScreenOptionSelected == 0) DecreaseOption();
            if (ScreenOptionSelected == 1) IncreaseOption();
            if (ScreenOptionSelected == 2) SettingMenu(0);
          }
          else {
            //settings menu (secondary page)
            
          }
        }
        else {
          if(ScreenCurrentMenu != 2) {
            NextDisplay();
          }
          else {
            ResetMilCodes();
          }
        }
      }
      else {
        if(ScreenCurrentMenu == 3) {
          SleepDevice();
        }
        else if(ScreenCurrentMenu == 4) {
          SettingMenu(0);
        }
        else if(ScreenCurrentMenu == 5) {
          SetNightMode();
        }
        else {
          MainMenu(); //Select Current Menu
        }
      }
    //}
    
    //AutoSaveEEPROM();
  }

  //Dual buttons
  if (buttonDual == ON) {
    if (!InMain) {
      if (ScreenCurrentMenu == 0) {
        NextDisplay();
      }
      else if (ScreenCurrentMenu == 1) {
        ResetPeaks();
      }
      else if (ScreenCurrentMenu == 2) {
        ResetMilCodes();
      }
      else if (ScreenCurrentMenu >= 4 && ScreenCurrentMenu < 12) {
        MainMenu();
      }
      else if (ScreenCurrentMenu == 12) {
        SettingMenu(0);
      }
      else if (ScreenCurrentMenu >= 13 && ScreenCurrentMenu <= 32) {
        MainMenu();
      }
      else {
        MainMenu();
      }
    }
    else {
      if (ScreenCurrentMenu != 3) {
        SettingMenu(0);
      }
      else {
        SleepDevice();
      }
    }
    
    //AutoSaveEEPROM();
  }
}

/*void BypassJ12() {
  J12Cut = true;
  ShowJ12 = false;
  WasAvailable = true;
  
  lcd.clear();
  ResetBufferIndex();
}*/

void ResetMilCodes() {
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(11);
  writeBigString(0, 0);
  ResetBufferIndex();
  bool Resetted = ResetMil();
  if (Resetted) GetInfosString(12);
  if (!Resetted) GetInfosString(13);
  writeBigString(0, 2);

  delay(1000);
  lcd.clear();
}

void ResetPeaks() {
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(11);
  writeBigString(0, 0);
  ResetBufferIndex();
  InitPeak();

  GetInfosString(8);
  writeBigString(2, 2);
  
  delay(1000);
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(12);
  writeBigString(0, 0);
  //writeBigString(0, 2);

  delay(1000);
  lcd.clear();
}

void NextDisplay() {
  if(ScreenCurrentMenu == 0) {
    ScreenCurrentPage++;
    if(ScreenCurrentPage > 8) ScreenCurrentPage = 1;
  }
  if(ScreenCurrentMenu == 1) {
    ScreenCurrentPeak++;
    if(ScreenCurrentPeak >= MaxDataValue) ScreenCurrentPeak = 0;
  }
  
  //SaveLoadEEPROM(true); //save
  ShowPage();
}

void MainMenu() {
  if (InMain) InMain = false;
  else InMain = true;
  if (ScreenCurrentMenu > 3) ScreenCurrentMenu = 0;
  
  //SaveLoadEEPROM(true); //save
  lcd.clear();

  if (InMain) AutoSaveEEPROM();
  
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

/*void SetWait() {
  WaitingQuick = true;
  WaitingDelay = debouncing*2;
}*/

void SettingMenu(int PartMenu) {
  InMain = false;
  if (PartMenu == 0) {
    if (ScreenCurrentMenu == 33) {
      ScreenCurrentMenu = ScreenSettingSelected;
    }
    else if (ScreenCurrentMenu == 12) {
      ScreenCurrentMenu = ScreenCurrentPage + 3;
    }
    else {
      ScreenCurrentMenu = 4;
    }
  }
  else if (PartMenu == 1) {
    ScreenCurrentPage = ScreenCurrentMenu - 3;
    ScreenSettingSelected = 0;
    ScreenCurrentMenu = 12;
  }
  else if (PartMenu == 2) {
    ScreenSettingSelected = ScreenCurrentMenu;
    ScreenOptionSelected = 0;
    ScreenCurrentMenu = 33;
  }
  lcd.clear();
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void SettingMenuNext() {
  int PartMenu = 0;
  if (ScreenCurrentMenu == 12) PartMenu = 1;
  
  ScreenCurrentMenu++;
  //if(ScreenCurrentMenu > 11 && PartMenu == 0) ScreenCurrentMenu = 4;
  if(ScreenCurrentMenu == 12 && PartMenu == 0) ScreenCurrentMenu++;
  if(ScreenCurrentMenu > 32 && PartMenu == 0) ScreenCurrentMenu = 4;
  
  if(ScreenCurrentMenu != 12 && PartMenu == 1) ScreenCurrentMenu = 12;
  
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void OptionMenuNext() {
  ScreenOptionSelected++;
  if (ScreenOptionSelected > 2) ScreenOptionSelected = 0;
  
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void SettingPageNext() {
  ScreenSettingSelected++;
  if (ScreenSettingSelected > 15) ScreenSettingSelected = 0;
  
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void SleepDevice() {
  if (!Sleeping) {
    BrightnessBuffer = Brightness;
    BrightnessBufferNight = BrightnessNight;
    Brightness = 0;
    BrightnessNight = 0;
    analogWrite(BackLightPin, 0);  // PWM values from 0 to 255 (0% – 100% duty cycle)
    //lcd.noBacklight();
    noBacklight();
    Sleeping = true;
    Serial1.end();
  } else {
    Brightness = BrightnessBuffer;
    BrightnessNight = BrightnessBufferNight;
    RefreshBackLight();
    //lcd.backlight();
    backlight();
    Sleeping = false;
    Serial1.begin(38400);
  }
  //SaveLoadEEPROM(true); //save
}

void SetNightMode() {
  if (!NightMode) {
    NightMode = true;
  }
  else {
    NightMode = false;
  }
  RefreshBackLight();
    
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void RefreshBackLight() {
  if (!NightMode) analogWrite(BackLightPin, Brightness);  // PWM values from 0 to 255 (0% – 100% duty cycle)
  if (NightMode) analogWrite(BackLightPin, BrightnessNight);  // PWM values from 0 to 255 (0% – 100% duty cycle)
}

void MainMenuNext() {
  ScreenCurrentMenu++;
  if(ScreenCurrentMenu > 5) ScreenCurrentMenu = 0;
  //if(ScreenCurrentMenu > 3) ScreenCurrentMenu = 0;
  
  //SaveLoadEEPROM(true); //save
  
  //delay(40);
  WaitingDelay = 40;
  WaitingQuick = false;
  //SetWait();
}

void ShowPage() {
  lcd.clear();

  ResetBufferIndex();
  GetInfosString(5);
  writeBigString(3, 0);
  
  ResetBufferIndex();
  if(ScreenCurrentMenu == 0) Add_String(String(ScreenCurrentPage));
  if(ScreenCurrentMenu == 1) Add_String(String(ScreenCurrentPeak));
  writeBigString(7, 2);

  WaitingDelay = 500;
  WaitingQuick = false;
  //_delay_ms(500);
  //lcd.clear();
}

/*void ShowMenu() {
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(6);
  writeBigString(3, 0);

  ResetBufferIndex();
  int XOffset = 0;
  if (ScreenCurrentMenu == 0) GetInfosString(7);
  if (ScreenCurrentMenu == 1) {
    GetInfosString(8);
    XOffset = 2;
  }
  if (ScreenCurrentMenu == 2) {
    GetInfosString(9);
    XOffset = 5;
  }
  if (ScreenCurrentMenu == 4) GetInfosString(24);
  
  writeBigString(XOffset, 2);
  
  WaitingDelay = 700;
  WaitingQuick = false;
  //_delay_ms(1000);
  //lcd.clear();
}*/
