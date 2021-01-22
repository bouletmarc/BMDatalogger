//#####################################################
//#####################################################
//#####################################################
/*
           THIS IS THE BM DEVS DATALOGGER

   THIS WORKS BY DATALOGGING BMTUNE ISR V3 PROTOCOL ON
   THE TX/RX SERIAL PORT. THIS WORKS WITH 2X BUTTONS
   NAVIGATION ONLY. IT ONLY WORKS FOR THE 20X04 LCD

   IF YOUR SCREEN DOESNT DISPLAY ANY CHARACTERS :
   FIND THE LINE 'LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);'
   AND REPLACE 0x3F BY 0x20 OR 0x27 OR 0x30

    ####################################################
      ALL CREDITS GOES TO :
   -Bouletmarc (BM Devs)
*/
//#####################################################
//#####################################################
//#####################################################

#include "Wire.h"
//#include <stdio.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
//#include <EnableInterrupt.h>
//#include <digitalWriteFast.h>
#include <SPI.h>
#include <SD.h>

//#####################################################
//#####################################################
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(I2CByte, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#include <LiquidCrystal.h>
const int rs = 37, en = 39, d4 = 41, d5 = 42, d6 = 43, d7 = 44;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void noBacklight() {
  digitalWrite(46, LOW);
}

void backlight() {
  RefreshBackLight();
}
//#####################################################
//#####################################################


//0x20-0x27 - 0x30 - 0x3F
//byte I2CByte = 0x27;
const int NextButton = 14;     //Atmega644P=20;     //Atmega328P=8
const int BackButton = 13;     //Atmega644P=19;     //Atmega328P=9
const int BackLightPin = A1;   //Atmega644P=12;   //Atmega328P=10
const int ContrastPin =  A0;   //Atmega644P=13;    //Atmega328P=None
const int ChipSelectPin = 8;  //Atmega644P=4;   //Atmega328P=None    CS Pin for SD Card
const int StatusLEDPin = 4;   //Atmega644P=1;    //Atmega328P=None    LED Pin for Status

byte Brightness = 255;
byte BrightnessNight = 110;
bool NightMode = false;
byte ContrastLevel = 150;

byte ScreenCurrentPage = 1;
byte ScreenCurrentPeak = 0;
byte ScreenCurrentMenu = 0;
byte ScreenSettingSelected = 0;
byte ScreenOptionSelected = 0;
byte ThisScreenIndex = 0;    //current display index number
byte XPos = 0;
byte YPos = 0;
char StringBuffer[20];
const int MaxDataValue = 79;
//bool EcuConnected = false;
bool InMain = true;
bool EngineRunning = false;
unsigned long last_datalog_time = 0;
bool Sleeping = false;
//bool J12Cut = true;
//bool ShowJ12 = false;
//bool WasAvailable = false;

int ScreenPage1[8] = {100, 0, 1, 2, 3, 9, 5, 11};
int ScreenPage2[8] = {200, 0, 7, 8, 14, 15, 28, 30};
int ScreenPage3[8] = {300, 0, 13, 20, 18, 19, 4, 5};
int ScreenPage4[8] = {100, 0, 100, 0, 18, 11, 19, 9};
int ScreenPage5[8] = {100, 0, 100, 0, 107, 0, 8, 16};
int ScreenPage6[8] = {100, 0, 61, 9, 53, 4, 57, 59};
int ScreenPage7[8] = {100, 0, 3, 12, 6, 4, 13, 26};
int ScreenPage8[8] = {41, 37, 35, 24, 25, 23, 17, 21};

const String BoardVersionStr = "2.0";
const String FirmwareVersionStr = "2.01";
byte ProgressBarMode = 2;
byte ProgressBarLeft = 0;
int Timeout = 150;
int Injectors_Size = 240;
byte O2Input = 0;
byte MapValue = 0;
byte UseCelcius = 1;
byte UseKMH = 1;
byte O2Type = 0;
double WBConversion[4] = {0, 1.3, 1, 0.71};
int WBModel = 0;
byte MapByte[4] = {186, 127, 254, 134};
byte Tranny[4] = {72, 113, 178, 214};
int TrannyModel = 0;
int MapModel = 0;
int Warning_RPM = 7600;
int Warning_IAT = 65;
int Warning_ECT = 107;

int mBarMin = -70;
int mBarMax = 1790;
int TempMin = -40;
int TempMax = 140;

int WaitingDelay = 0;
bool WaitingQuick = false;

const int SettingVersion = 3;
//int TimeoutCount = 0;
byte LastChecksum = 0;
const long AutoSaveTime = 120000;
unsigned long last_save_time = 0;

bool SDDetected = true;
bool SDLogging = true;

File myFile;
unsigned int SDFileCount = 0;

//#####################################################

void setup() {
  FirstLoadEEPROM();

  pinMode(BackButton, INPUT_PULLUP);
  pinMode(NextButton, INPUT_PULLUP);

  pinMode(StatusLEDPin, OUTPUT);
  digitalWrite(StatusLEDPin, HIGH);

  pinMode(BackLightPin, OUTPUT);
  RefreshBackLight();
  //pinMode(ContrastPin,OUTPUT);
  //analogWrite(ContrastPin, ContrastLevel);  // PWM values from 0 to 255 (0% – 100% duty cycle)

  //#######################################################
  //Atmega644 Interrupt
  //enableInterrupt(BackButton, pin_ISR1, CHANGE);
  //enableInterrupt(NextButton, pin_ISR2, CHANGE);
  
  digitalWrite(38, LOW);  //RW Pins on Atmega64A
  //#######################################################

  ReCalcValueRange();

  //###################
  //screen start
  lcd.begin(20, 4);
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(20);
  PrintTextAnimated(20, 4, 0);

  //delay(200);
  ResetBufferIndex();
  Add_String(BoardVersionStr);
  //PrintTextAnimated(3, 15, 0);
  writeBigStringAnimated(6, 1);

  //delay(200);
  ResetBufferIndex();
  Add_String("Firmware V" + FirmwareVersionStr);
  PrintTextAnimated(20, 3, 3);

  /*delay(200);
    ResetBufferIndex();
    Add_String(FirmwareVersionStr);
    PrintTextAnimated(20, 8, 2);*/

  /*delay(200);
    ResetBufferIndex();
    GetInfosString(21);
    PrintTextAnimated(20, 3, 3);*/

  delay(700);
  //lcd.clear();
  //###################

  Serial.begin(38400);
  Serial1.begin(38400);
  //ScanForI2C();
  //ScanForSD();

  digitalWrite(StatusLEDPin, LOW);
  lcd.clear();
}

void ScanForSD() {
  if (!SD.begin(ChipSelectPin)) {
    SDDetected = false;
    Serial.println("Card failed, or not present");
  }

  if (SDDetected) {
    SDFileCount = 0;
    /*while (SD.exists("BMDatalogger" + SDFileCount + ".bml")) {
      SDFileCount++;
      Serial.println("BMDatalogger" + SDFileCount + ".bml already exists!");
      }*/
  }
}

void ReCalcValueRange() {
  mBarMin = (int) ((((long) MapByte[1] * 256) + (long) MapByte[0]) - 32768);
  mBarMax = (int) ((((long) MapByte[3] * 256) + (long) MapByte[2]) - 32768);

  if (UseCelcius == 0) {
    TempMin = TempMin * 1.8 + 32.0;
    TempMax = TempMax * 1.8 + 32.0;
    Warning_IAT = Warning_IAT * 1.8 + 32.0;
    Warning_ECT = Warning_ECT * 1.8 + 32.0;
  }
}

//#####################################################

void loop() {
  RefreshBackLight();
  //analogWrite(ContrastPin, ContrastLevel);  // PWM values from 0 to 255 (0% – 100% duty cycle)
  //ConnectBT();
  //CheckButtons();

  if (millis() - last_save_time > AutoSaveTime) {
    AutoSaveEEPROM();
  }

  //############################
  while (WaitingDelay > 0) {
    if (InMain && WaitingQuick) ScreenMain();
    if (!InMain && WaitingQuick) Display();
    delay(1);
    WaitingDelay--;
    CheckButtons();
    if (WaitingDelay <= 0) {
      //if (!WaitingQuick) lcd.clear();
      //if (WaitingQuick) WaitingQuick = false;
      WaitingQuick = false;
    }
    //if (WaitingQuick) WaitingQuick = false;
  }
  //############################

  if (millis() - last_datalog_time > Timeout) {
    //if (TimeoutCount >= Timeout) {
    /*if (!J12Cut) {
      ScreenJ12();
      }
      else {*/
    GetData();
    SetEngineRunning();
    ApplyPeak();
    //TimeoutCount = 0;
    //}
    last_datalog_time = millis();
  }

  //if (!ShowJ12) {
  SetSpeedTime();
  GetWarnings();

  if (InMain) ScreenMain();
  if (!InMain) Display();
  //}

  CheckButtons();

  //_delay_us(100);
  //TimeoutCount++;
}

//#####################################################

/*void ScanForI2C() {
  // Leonardo: wait for serial port to connect
  while (!Serial) { }

  //scan
  byte count = 0;
  Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      if (i != I2CByte)
      {
        I2CByte = i;

        Serial.println ();
        Serial.print ("I2CByte Address not set correctly, please set to: ");
        Serial.print ("0x");
        Serial.print (i, HEX);

        //Enless Loop
        //while(true) { } //desactivated due to New AutoConnect
      }
      count++;
    }
  }
}*/

//#####################################################

void FirstLoadEEPROM() {
  if (EEPROM.read(0) != SettingVersion) {
    SaveLoadEEPROM(true);   //save (never create this version settings)
  }
  SaveLoadEEPROM(false);  //load
  LastChecksum = GetSettingsSum();
}

void AutoSaveEEPROM() {
  last_save_time = millis();

  byte NewChecksum = GetSettingsSum();
  if (NewChecksum != LastChecksum) {
    if (EEPROM.read(1) != NewChecksum) {
      EEPROM.write(0, SettingVersion);
      EEPROM.write(1, NewChecksum);
      SaveLoadEEPROM(true);   //save
      LastChecksum = GetSettingsSum();
    }
  }

  //SaveLoadEEPROM(false);  //load
  //LastChecksum = GetSettingsSum();
}

byte GetSettingsSum() {
  byte num = 0;
  num = (byte) (num + SettingVersion);
  num = (byte) (num + ScreenCurrentPage);
  num = (byte) (num + ScreenCurrentPeak);
  num = (byte) (num + ScreenCurrentMenu);
  if (Sleeping) num = (byte) (num + 1);
  if (InMain) num = (byte) (num + 1);
  num = (byte) (num + Brightness);
  num = (byte) (num + BrightnessNight);
  if (NightMode) num = (byte) (num + 1);
  num = (byte) (num + ScreenSettingSelected);
  num = (byte) (num + ScreenOptionSelected);
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage1[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage1[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage2[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage2[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage3[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage3[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage4[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage4[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage5[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage5[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage6[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage6[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage7[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage7[i]));
  }
  for (byte i = 1; i < 8; i++)  {
    num = (byte) (num + GetMSBFromInt(ScreenPage8[i]));
    num = (byte) (num + GetLSBFromInt(ScreenPage8[i]));
  }
  num = (byte) (num + ProgressBarMode);
  num = (byte) (num + ProgressBarLeft);

  num = (byte) (num + GetMSBFromInt(Timeout));
  num = (byte) (num + GetLSBFromInt(Timeout));
  num = (byte) (num + GetMSBFromInt(Injectors_Size));
  num = (byte) (num + GetLSBFromInt(Injectors_Size));

  num = (byte) (num + O2Input);
  num = (byte) (num + MapValue);
  num = (byte) (num + UseCelcius);
  num = (byte) (num + UseKMH);
  num = (byte) (num + O2Type);
  //missing WB table
  for (byte i = 1; i < 4; i++)  {
    //(int) (ThisDouble * 100)
    num = (byte) (num + GetMSBFromInt((int) (WBConversion[i] * 100)));
    num = (byte) (num + GetLSBFromInt((int) (WBConversion[i] * 100)));
    //num = (byte) (num + GetMSBFromDouble(WBConversion[i]));
    //num = (byte) (num + GetLSBFromDouble(WBConversion[i]));
  }
  num = (byte) (num + WBModel);
  for (byte i = 1; i < 4; i++)  num = (byte) (num + MapByte[i]);
  for (byte i = 1; i < 4; i++)  num = (byte) (num + Tranny[i]);
  num = (byte) (num + TrannyModel);
  num = (byte) (num + MapModel);

  num = (byte) (num + GetMSBFromInt(Warning_RPM));
  num = (byte) (num + GetLSBFromInt(Warning_RPM));
  num = (byte) (num + GetMSBFromInt(Warning_IAT + 40));
  num = (byte) (num + GetLSBFromInt(Warning_IAT + 40));
  num = (byte) (num + GetMSBFromInt(Warning_ECT + 40));
  num = (byte) (num + GetLSBFromInt(Warning_ECT + 40));
  num = (byte) (num + GetMSBFromInt(mBarMin + 300));
  num = (byte) (num + GetLSBFromInt(mBarMin + 300));
  num = (byte) (num + GetMSBFromInt(mBarMax));
  num = (byte) (num + GetLSBFromInt(mBarMax));
  num = (byte) (num + GetMSBFromInt(TempMin + 40));
  num = (byte) (num + GetLSBFromInt(TempMin + 40));
  num = (byte) (num + GetMSBFromInt(TempMax + 40));
  num = (byte) (num + GetLSBFromInt(TempMax + 40));

  return num;
}

/*byte GetMSBFromDouble(double ThisDouble) {
  int ThisInt = (int) (ThisDouble * 100);
  return GetMSBFromInt(int ThisInt);
  }

  byte GetLSBFromDouble(double ThisDouble) {
  int ThisInt = (int) (ThisDouble * 100);
  return GetLSBFromInt(int ThisInt);
  }*/

byte GetMSBFromInt(int ThisInt) {
  byte MSB = (byte) (ThisInt / 256);
  return MSB;
}

byte GetLSBFromInt(int ThisInt) {
  byte MSB = (byte) (ThisInt / 256);
  byte LSB = (byte) (ThisInt - MSB);
  return LSB;
}

void SaveLoadEEPROM(bool IsSaving) {
  int CurrAddr = 5;

  if (IsSaving) EEPROM.write(CurrAddr, ScreenCurrentPage);
  else ScreenCurrentPage = EEPROM.read(CurrAddr);

  ScreenCurrentPeak = CheckThisByte(IsSaving, CurrAddr, ScreenCurrentPeak);
  CurrAddr++;
  ScreenCurrentMenu = CheckThisByte(IsSaving, CurrAddr, ScreenCurrentMenu);
  CurrAddr++;
  Sleeping = CheckThisBool(IsSaving, CurrAddr, Sleeping);
  CurrAddr++;
  InMain = CheckThisBool(IsSaving, CurrAddr, InMain);
  CurrAddr++;
  Brightness = CheckThisByte(IsSaving, CurrAddr, Brightness);
  CurrAddr++;
  BrightnessNight = CheckThisByte(IsSaving, CurrAddr, BrightnessNight);
  CurrAddr++;
  NightMode = CheckThisBool(IsSaving, CurrAddr, NightMode);
  CurrAddr++;
  ScreenSettingSelected = CheckThisByte(IsSaving, CurrAddr, ScreenSettingSelected);
  CurrAddr++;
  ScreenOptionSelected = CheckThisByte(IsSaving, CurrAddr, ScreenOptionSelected);
  CurrAddr++;

  //#####################################################################
  for (byte i = 1; i < 8; i++)  {
    ScreenPage1[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage1[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage2[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage2[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage3[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage3[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage4[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage4[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage5[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage5[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage6[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage6[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage7[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage7[i]);
    CurrAddr++;
    CurrAddr++;
  }
  for (byte i = 1; i < 8; i++)  {
    ScreenPage8[i] = CheckThisInt(IsSaving, CurrAddr, ScreenPage8[i]);
    CurrAddr++;
    CurrAddr++;
  }
  //#####################################################################

  ProgressBarMode = CheckThisByte(IsSaving, CurrAddr, ProgressBarMode);
  CurrAddr++;
  ProgressBarLeft = CheckThisByte(IsSaving, CurrAddr, ProgressBarLeft);
  CurrAddr++;

  Timeout = CheckThisInt(IsSaving, CurrAddr, Timeout);
  CurrAddr++;
  CurrAddr++;
  Injectors_Size = CheckThisInt(IsSaving, CurrAddr, Injectors_Size);
  CurrAddr++;
  CurrAddr++;

  O2Input = CheckThisByte(IsSaving, CurrAddr, O2Input);
  CurrAddr++;
  MapValue = CheckThisByte(IsSaving, CurrAddr, MapValue);
  CurrAddr++;
  UseCelcius = CheckThisByte(IsSaving, CurrAddr, UseCelcius);
  CurrAddr++;
  UseKMH = CheckThisByte(IsSaving, CurrAddr, UseKMH);
  CurrAddr++;
  O2Type = CheckThisByte(IsSaving, CurrAddr, O2Type);
  CurrAddr++;

  //Missing WB Conversion (double here)
  for (byte i = 1; i < 4; i++)  {
    WBConversion[i] = CheckThisDouble(IsSaving, CurrAddr, WBConversion[i]);
    CurrAddr++;
    CurrAddr++;
  }

  WBModel = CheckThisByte(IsSaving, CurrAddr, WBModel);
  CurrAddr++;

  for (byte i = 1; i < 4; i++)  {
    MapByte[i] = CheckThisByte(IsSaving, CurrAddr, MapByte[i]);
    CurrAddr++;
  }
  for (byte i = 1; i < 4; i++)  {
    Tranny[i] = CheckThisByte(IsSaving, CurrAddr, Tranny[i]);
    CurrAddr++;
  }

  TrannyModel = CheckThisByte(IsSaving, CurrAddr, TrannyModel);
  CurrAddr++;
  MapModel = CheckThisByte(IsSaving, CurrAddr, MapModel);
  CurrAddr++;

  Warning_RPM = CheckThisInt(IsSaving, CurrAddr, Warning_RPM);
  CurrAddr++;
  CurrAddr++;
  Warning_IAT = CheckThisInt(IsSaving, CurrAddr, Warning_IAT + 40) - 40;
  CurrAddr++;
  CurrAddr++;
  Warning_ECT = CheckThisInt(IsSaving, CurrAddr, Warning_ECT + 40) - 40;
  CurrAddr++;
  CurrAddr++;
  mBarMin = CheckThisInt(IsSaving, CurrAddr, mBarMin + 300) - 300;
  CurrAddr++;
  CurrAddr++;
  mBarMax = CheckThisInt(IsSaving, CurrAddr, mBarMax);
  CurrAddr++;
  CurrAddr++;
  TempMin = CheckThisInt(IsSaving, CurrAddr, TempMin + 40) - 40;
  CurrAddr++;
  CurrAddr++;
  TempMax = CheckThisInt(IsSaving, CurrAddr, TempMax + 40) - 40;
  CurrAddr++;
  CurrAddr++;
}

//##################################################################

double CheckThisDouble(bool IsSaving, int CurrAddr, double ThisDouble) {
  if (IsSaving) {
    int ThisInt = (int) (ThisDouble * 100);
    CheckThisInt(IsSaving, CurrAddr, ThisInt);
  }
  else {
    return (double) ((double) CheckThisInt(IsSaving, CurrAddr, 9999) / 100.0);
  }
  return ThisDouble;
}

int CheckThisInt(bool IsSaving, int CurrAddr, int ThisInt) {
  if (IsSaving) {
    byte MSB = (byte) (ThisInt / 256);
    byte LSB = (byte) (ThisInt - MSB);
    WriteSingleByte(CurrAddr, MSB);
    CurrAddr++;
    WriteSingleByte(CurrAddr, LSB);
  }
  else {
    byte MSB = ReadSingleByte(CurrAddr);
    CurrAddr++;
    byte LSB = ReadSingleByte(CurrAddr);
    return ((int) LSB + ((int) MSB * 256));
  }
  return ThisInt;
}


bool CheckThisBool(bool IsSaving, int CurrAddr, bool ThisBool) {
  if (IsSaving) {
    if (ThisBool) WriteSingleByte(CurrAddr, 1);
    else WriteSingleByte(CurrAddr, 0);
  }
  else {
    if (ReadSingleByte(CurrAddr) == 1) return true;
    else return false;
    //return ReadSingleByte(CurrAddr);
  }
  return ThisBool;
}

byte CheckThisByte(bool IsSaving, int CurrAddr, byte ThisByte) {
  if (IsSaving) {
    WriteSingleByte(CurrAddr, ThisByte);
  }
  else {
    return ReadSingleByte(CurrAddr);
  }
  return ThisByte;
}

void WriteSingleByte(int CurrAddr, byte ThisByte) {
  CurrAddr++;
  EEPROM.write(CurrAddr, ThisByte);
}

byte ReadSingleByte(int CurrAddr) {
  CurrAddr++;
  return EEPROM.read(CurrAddr);
}
//###################################################################
