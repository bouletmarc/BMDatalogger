int PeakValuesMin[MaxDataValue];
int PeakValuesMax[MaxDataValue];
int PeakMinValue = 0;
int PeakMaxValue = 1;
byte PeakInitialized = 0;
bool PeakSet = false;

void InitPeak() {
  for (int i=0; i < MaxDataValue; i++) {
    ThisScreenIndex = i;
    int Value = (int) GetInt();
    PeakValuesMin[i] = Value;
    PeakValuesMax[i] = Value;
  }
  PeakInitialized = 1;
}

void SetPeakValue(const int minValue, const int maxValue) {
  if (PeakInitialized == 0) InitPeak();
  PeakMinValue = minValue;
  PeakMaxValue = maxValue;

  PeakSet = true;
}

void ApplyPeak() {
  for (int i=0; i < MaxDataValue; i++) {
    ThisScreenIndex = i;
    SetPeak();
    int ThisValue = (int) GetInt();
    if (ThisValue < PeakValuesMin[ThisScreenIndex]) PeakValuesMin[ThisScreenIndex] = ThisValue;
    if (ThisValue > PeakValuesMax[ThisScreenIndex]) PeakValuesMax[ThisScreenIndex] = ThisValue;
  }
}

void SetPeak() {
  PeakSet = false;
  if (ThisScreenIndex == 0) SetPeakValue(0,11000);
  if (ThisScreenIndex == 1) SetPeakValue(TempMin, TempMax);
  if (ThisScreenIndex == 1) SetPeakValue(TempMin, TempMax);
  if (ThisScreenIndex == 3) SetPeakValue(0,100);
  if (ThisScreenIndex == 4) SetPeakValue(10,20);
  if (ThisScreenIndex == 5) SetPeakValue(-6,60);
  if (ThisScreenIndex == 6) SetPeakValue(0,20);
  if (ThisScreenIndex == 7) SetPeakValue(0,50);
  if (ThisScreenIndex == 8) SetPeakValue(-100,100);
  if (ThisScreenIndex == 9) SetPeakValue(mBarMin, mBarMax);
  if (ThisScreenIndex == 10) SetPeakValue(0,40);
  if (ThisScreenIndex == 11) SetPeakValue(0,300);
  if (ThisScreenIndex == 13) SetPeakValue(0,18);
  if (ThisScreenIndex == 16) SetPeakValue(0,3000);
  if (ThisScreenIndex == 18) SetPeakValue(2,18);
  if (ThisScreenIndex == 19) SetPeakValue(2,18);
  if (ThisScreenIndex == 22) SetPeakValue(0,18);
  if (ThisScreenIndex == 26) SetPeakValue(0,5);
  if (ThisScreenIndex == 59) SetPeakValue(-6,60);
  if (ThisScreenIndex == 68) SetPeakValue(114, 3800);
  if (ThisScreenIndex == 69) SetPeakValue(0, 100);
  if (ThisScreenIndex == 70) SetPeakValue(0, 255);
  if (ThisScreenIndex == 71) SetPeakValue(0, 255);
  if (ThisScreenIndex == 72) SetPeakValue(0, 255);
  if (ThisScreenIndex == 73) SetPeakValue(0, 255);
  if (ThisScreenIndex == 74) SetPeakValue(0, 255);
  if (ThisScreenIndex == 75) SetPeakValue(0, 60);
  if (ThisScreenIndex == 76) SetPeakValue(0, 60);
  if (ThisScreenIndex == 77) SetPeakValue(0, 60);
  if (ThisScreenIndex == 78) SetPeakValue(0, 100);
  if (ThisScreenIndex == 79) SetPeakValue(0, 100);
  
  if (!PeakSet) SetPeakValue(0,1);
}

double GetPeakPercent(int value) {
  SetPeak();
  if (value < PeakMinValue) return 0.0;
  if (value > PeakMaxValue) return 100.0;
  return map((double) value, (double) PeakMinValue, (double) PeakMaxValue, (double) 0, (double) 100);
}

int GetPeakMin() {
  return PeakValuesMin[ThisScreenIndex];
}

int GetPeakMax() {
  return PeakValuesMax[ThisScreenIndex];
}
