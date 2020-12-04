const int Array_Size    = 52;
byte Datalog_Bytes[Array_Size];
unsigned long CurrentSDWrite = 0;

// ect, iat, o2, baro, map
// tps, rpmlo, rpmhi, vtec, locam
// hicam, column, vss, injlo, injhi
// ign, knonk, (crank|batt)    (crank for crome 1.2, batt for crome 1.4)

//Crome 1.2 Protocol
const byte Crome12_Bytes[18] = {
  0x10, 0x11, 0x12, 0x13, 0x14,
  0x15, 0x16, 0x17, 0x18, 0x19,
  0x1A, 0x1B, 0x20, 0x21, 0x08,
  0x23, 0x24, 0x25
};

//Crome 1.4 QD2 Protocol
const byte Crome14_Bytes[18] = {
  0x1D, 0x1B, 0x20, 0x1E, 0x14,
  0x15, 0x10, 0x11, 0x22, 0x12,
  0x13, 0x16, 0x1C, 0x17, 0x18,
  0x19, 0x1A, 0x22  //0x22 or 0x1F for Batt
};

//################################################

// ect, iat, map, baro, tps
// o2, rpmlo, rpmhi, rows, column
// vtec, vss, err1, err2, err3
// (fuello, fuelhi, gear, eld, ign) (NG63++)

//NG60-NG62 Protocol
const byte NG60_Bytes[15] = {
  0x30, 0x32, 0xF8, 0x34, 0x39,
  0xFB, 0xFA, 0x47, 0xFE, 0xFD,
  0x18, 0x6C, 0x2B, 0x2C, 0x2D,
};

//NG63 Protocol
const byte NG63_Bytes[20] = {
  0x30, 0x32, 0xF8, 0x34, 0x39,
  0xFB, 0xFA, 0x47, 0x3B, 0xFD,
  0x18, 0x6C, 0x2B, 0x2C, 0x2D,
  0x70, 0x6F, 0xFE, 0xFC, 0x63
};

/*void GetJ12Cut() {
  J12Cut = false;
  WasAvailable = false;
  Serial.write((byte) 16);
  _delay_ms(500);
  if (Serial.available()) {
    WasAvailable = true;
    if (Serial.read() == 0xcd) J12Cut = true;
  }
}*/

void WriteToSD() {
  unsigned long FLenght = ((CurrentSDWrite * 72) + 14);
  unsigned long long_2 = ((int)((FLenght - 0x7b) - 0x10L)) / (0x7b + 1);
  //this.long_3 = struct12_1.long_3;

  myFile = SD.open("BMDatalogger.bml", FILE_WRITE);
  //myFile = SD.open("BMDatalogger" + SDFileCount + ".bml", FILE_WRITE);
  if (CurrentSDWrite == 0)
  {
      myFile.write((const uint8_t *) 0x42, 1);
      myFile.write((const uint8_t *) 0x4d, 1);
      myFile.write((const uint8_t *) 0x54, 1);
      myFile.write((const uint8_t *) 0x75, 1);
      myFile.write((const uint8_t *) 0x6e, 1);
      myFile.write((const uint8_t *) 0x65, 1);
      myFile.write((const uint8_t *) 0x2e, 1);
      myFile.write((const uint8_t *) 0x62, 1);
      myFile.write((const uint8_t *) 0x6d, 1);
      myFile.write((const uint8_t *) 0x6c, 1);
      myFile.write((const uint8_t *) 0x06, 1);
      myFile.write((const uint8_t *) 0x00, 1);
      myFile.write((const uint8_t *) 0x7b, 1);
      myFile.write((const uint8_t *) 0x00, 1);
  }
  
  myFile.write((const uint8_t *) Datalog_Bytes[0], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[1], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[2], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[3], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[4], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[5], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[6], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[7], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[8], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[9], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[10], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[11], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[12], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[13], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[14], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[15], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[16], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[17], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[18], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[19], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[20], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[21], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[22], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[23], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[24], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[25], 1);
  
  myFile.write((const uint8_t *) GetByte1(CurrentSDWrite + 1), 1);
  myFile.write((const uint8_t *) GetByte2(CurrentSDWrite + 1), 1);
  
  myFile.write((const uint8_t *) GetByte1(Timeout), 1);
  myFile.write((const uint8_t *) GetByte2(Timeout), 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[26], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[27], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[28], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[29], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[30], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[31], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[32], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[33], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[34], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[35], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[36], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[37], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[38], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[39], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[40], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[41], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[42], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[43], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[44], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[45], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[46], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[47], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[48], 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[49], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[50], 1);

  myFile.write((const uint8_t *) GetWBByte(), 1);
  
  myFile.write((const uint8_t *) Datalog_Bytes[8], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[9], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[10], 1);
  myFile.write((const uint8_t *) Datalog_Bytes[11], 1);

  //NOT FINISHED HERE //float_0 in bmtune
  
  //myFile.write((const uint8_t *)&Datalog_Bytes, sizeof(Datalog_Bytes));
  myFile.close();

  CurrentSDWrite++;
}

byte GetByte1(long ThisNumber) {
  int Divider = ThisNumber / 255;
  return ThisNumber - (Divider * 255);
}

byte GetByte2(long ThisNumber) {
  return ThisNumber / 255;
}

void GetData(){
  //digitalWrite(StatusLEDPin, HIGH);
  if(Serial1.available()) {
    int Tries = 0;
    while (Serial1.available() < 52 && Tries < 50) {
      //delayMicroseconds(1);
      delay(1);
      Tries++;
    }
    for (int i = 0; i < Array_Size; i++) {
       Datalog_Bytes[i] = Serial1.read();
    }
  }
      
  Serial1.flush();
  Serial1.write(" ");
  //digitalWrite(StatusLEDPin, LOW);

  //FakeValue += 1;
  //if (FakeValue >= 180) FakeValue = 0;
}

bool ResetMil() {
  bool MilResetted = false;
  Serial1.write((byte) 80);
  delay(500);
  if (Serial1.available()) {
    byte MilReadByte[4] = {0,0,0,0};
    for (int i = 0; i < 4; i++) MilReadByte[i] = Serial1.read();
    if (MilReadByte[1] == 80) MilResetted = true;
  }
  return MilResetted;
}

void GetMil() {
  int Displayed = 0;
  for (int i = 1; i <= 8; i++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[12], i - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(i));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int j = 1; j <= 8; j++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[13], j - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(j + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int k = 1; k <= 8; k++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[14], k - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil((k + 8) + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int m = 1; m <= 8; m++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[15], m - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(((m + 8) + 8) + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }

  //Nothing Displayed
  if (Displayed == 0) {
    ResetBufferIndex();
    GetInfosString(10);
    writeBigString(0, 2);
  }

  //Reset Overlay if displayed
  if (Displayed == 1) {
    ResetBufferIndex();
    PrintText(10, 10, 2);
  }
  if (Displayed == 2) {
    ResetBufferIndex();
    PrintTextLenght(0, 3);
  }
  if (Displayed == 3) {
    ResetBufferIndex();
    PrintText(10, 10, 3);
  }
}

int FixMil(int Value) {
  switch (Value) {
      case 0x18:
          return 30;
      case 0x19:
          return 0x1f;
      case 0x1a:
          return 0x24;
      case 0x1b:
          return 0x29;
      case 0x1c:
          return 0x2b;
  }
  //if (Value >= 0x18) return 0;
  return Value;
}

long Long2Bytes(const byte ThisByte1, const byte ThisByte2) {
  return ((long) ThisByte2 * 256) + (long) ThisByte1;
}

float GetTemperature(const byte ThisByte) {
  float ThisTemp = (float) ThisByte / 51;
  ThisTemp = (0.1423*pow(ThisTemp,6)) - (2.4938*pow(ThisTemp,5))  + (17.837*pow(ThisTemp,4)) - (68.698*pow(ThisTemp,3)) + (154.69*pow(ThisTemp,2)) - (232.75*ThisTemp) + 284.24;
  ThisTemp = ((ThisTemp - 32)*5)/9;

  if (UseCelcius == 0)
    ThisTemp = ThisTemp * 1.8 + 32.0;
  
  return ThisTemp;
}

double GetVolt(const byte ThisByte) {
  return (double) ThisByte * 0.0196078438311815;
}

float GetDuration(const int ThisInt) {
  return ((float) ThisInt * 3.20000004768372) / 1000.0;
}

byte GetActivated(byte ThisByte, const int ThisPos, const bool Reversed) {
  int bitArray[8];
  for (int i=0; i < 8; ++i ) {
    bitArray[i] = ThisByte & 1;
    ThisByte = ThisByte >> 1;
  }

  if (Reversed)
    return bitArray[ThisPos] ? (byte) 0 : (byte) 1;
  return bitArray[ThisPos] ? (byte) 1 : (byte) 0;
}

float GetInstantConsumption(){
  if (GetVssKMH() == 0) return 0;
  //float hundredkm = ((60 / GetVssKMH()) * 100) / 60;                      //minutes needed to travel 100km (OLD)
  float hundredkm = 6000 / GetVssKMH();                                     //minutes needed to travel 100km
  float fuelc = (hundredkm * ((Injectors_Size / 100) * GetDuty())) / 1000;     
  return constrain(fuelc * 4, 0.0, 50.0);                                   //Vary between 0-50 L/100km
}

float GetDuty(){
  return ((float) GetRpm() * (float) GetInjDurr()) / 1200;
}

int GetInjDurr(){
  //return (int) (Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 352);
  return GetDuration((int) Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]));
}

int GetEct(){
  return constrain(GetTemperature(Datalog_Bytes[0]), TempMin, TempMax);
}

int GetIat(){
  return constrain(GetTemperature(Datalog_Bytes[1]), TempMin, TempMax);                  
}

byte GetWBByte(){
  byte WBByte = 0;
  if (O2Input == 0) WBByte = Datalog_Bytes[2];
  if (O2Input == 1) WBByte = Datalog_Bytes[24];
  if (O2Input == 2) WBByte = Datalog_Bytes[44];
  if (O2Input == 3) WBByte = Datalog_Bytes[45];
  return WBByte;
}

double GetO2(){
  byte WBByte = 0;
  if (O2Input == 0) WBByte = Datalog_Bytes[2];
  if (O2Input == 1) WBByte = Datalog_Bytes[24];
  if (O2Input == 2) WBByte = Datalog_Bytes[44];
  if (O2Input == 3) WBByte = Datalog_Bytes[45];
  double RTND = 0.0;
  if (O2Type == 0) RTND = constrain((double) InterpolateWB(GetVolt(WBByte)) * 14.7, 10, 20);
  if (O2Type == 1) RTND = constrain((double) InterpolateWB(GetVolt(WBByte)), 0, 5);
  if (O2Type == 2) RTND = constrain((double) GetVolt(WBByte), 0, 16);

  //return RoundThis(1, RTND);
  return RTND;
}

double InterpolateWB(double ThisDouble) {
  if (ThisDouble < WBConversion[0]) return WBConversion[1];
  if (ThisDouble > WBConversion[2]) return WBConversion[3];
  return (WBConversion[1] + (((ThisDouble - WBConversion[0]) * (WBConversion[3] - WBConversion[1])) / (WBConversion[2] - WBConversion[0])));
}

int GetMBar() {
  long Value = (long) Datalog_Bytes[4];
  long MapLow = (long) mBarMin + 32768;
  long MapHigh = (long) mBarMax + 32768;
                
  return (int) ((((Value * (MapHigh - MapLow)) / 255) + MapLow) - 32768);
}

int GetMap(){
  int mBar = GetMBar();
  if (MapValue == 0) return constrain(mBar, mBarMin, mBarMax);
  else if (MapValue == 1) {
    if (mBar <= 1013) return 0;
    else return constrain((int) (((float) mBar - 1013) * 0.01450377), 0, 40); //GetValuePSI(ThisInt);
  }
  else if (MapValue == 2) return constrain((int) round((double) mBar * 0.1), 0, 105); //GetValueKPa(ThisInt);
  else return 0;
}

double GetBoost(){
  int ThisInt = GetMBar();
  if (ThisInt <= 1013) return 0;
  else return (double) (((double) ThisInt - 1013) * 0.0145037695765495);
}

unsigned int GetTps(){
  return constrain((int) round(((double) Datalog_Bytes[5] - 25.0) / 2.04), 0, 100);
  //return constrain((0.4716  * Datalog_Bytes[5]) - 11.3184, 0, 100);    
}

unsigned int GetRpm(){
  //return (int) (1875000/Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]));  //unused
  
  int rpm = (int) (1851562/Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]));
  return constrain(rpm, 0, 11000);
}

void SetEngineRunning() {
  if (GetRpm() < 400) EngineRunning = false;
  else EngineRunning = true;
}

unsigned int GetVss(){
  if (UseKMH == 1) return (int) Datalog_Bytes[16];
  return (int) round((float) Datalog_Bytes[16] / 1.6f);
}

unsigned int GetVssKMH(){
  return (unsigned int) Datalog_Bytes[16];
}

double GetInjFV() {
    return (double) Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 4.0;
}

int GetIgn(){
  return constrain((0.25 * Datalog_Bytes[19]) - 6, -6, 60);
}

float GetBattery(){  
  return constrain((26.0 * Datalog_Bytes[25]) / 270.0, 0, 18);
}

int GetIACVDuty(){
  return constrain((int) (Long2Bytes(Datalog_Bytes[49], Datalog_Bytes[50]) / 327.68) - 100, -100, 100);
}

double GetMapVolt(){
  return constrain(GetVolt(Datalog_Bytes[4]), 0, 5);
}

double GetTPSVolt(){
  return constrain(GetVolt(Datalog_Bytes[5]), 0, 5);
}

//###############################

double GetELDVolt(){
  return GetVolt(Datalog_Bytes[24]);
}


unsigned int GetGear(){
  long VSS = (long) GetVssKMH();
  long FAKERPM = Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]);
  if (VSS == 0 | GetRpm() == 0) return 0;
  long num = ((VSS * 256) * FAKERPM) / 65535;
  for (int i = 0; i < 4; i++) if (num < (long) Tranny[i]) return i + 1;
  return 5;
}

int GetIgnTable(){
  return (0.25 * Datalog_Bytes[20]) - 6;
}

//###############################

bool GetSensorsActived(int ThisB, int ThisI){
  return (bool) GetActivated(Datalog_Bytes[ThisB], ThisI, false);
}

//###############################

int GetBaro(){
  return (int) round((double) ((int) Datalog_Bytes[3] / 2 + 24) * 7.221 - 59.0);
}

double GetECTFC(){
  return GetFC(Datalog_Bytes[26], 128);
}

double GetO2Short(){
  return (double) GetFC(Long2Bytes(Datalog_Bytes[27], Datalog_Bytes[28]), 32768);
}

double GetO2Long(){
  return (double) GetFC(Long2Bytes(Datalog_Bytes[29], Datalog_Bytes[30]), 32768);
}

double GetIATFC(){
  return (double) GetFC(Long2Bytes(Datalog_Bytes[31], Datalog_Bytes[32]), 32768);
}

double GetVEFC(){
  return GetFC(Datalog_Bytes[33], 128);
}

float GetIATIC(){
  return GetIC(Datalog_Bytes[34]);
}

float GetECTIC(){
  return GetIC(Datalog_Bytes[35]);
}

float GetGEARIC(){
  return GetIC(Datalog_Bytes[36]);
}

double GetEBCBaseDuty(){
  return GetEBC(Datalog_Bytes[40]);
}

double GetEBCDuty(){
  return GetEBC(Datalog_Bytes[41]);
}

float GetIC(byte ThisByte) {
  if ((int) ThisByte == 128)
    return 0.0f;
  if ((int) ThisByte < 128)
    return (float) (128 - (int) ThisByte) * -0.25f;
  return (float) ((int) ThisByte - 128) * 0.25f;
}

double GetFC(long ThisByte, long ThisLong) {
  double num = (double) ThisByte / (double) ThisLong;
  //if (CorrectionUnits == "multi")
    return round((num) * 100) / 100;
  //return round(num * 100.0 - 100.0);
}

double GetEBC(byte ThisByte) {
  double num = (double) ThisByte / 2.0;
  if (num > 100.0) num = 100.0;
  return round((num * 10)) / 10;
}
