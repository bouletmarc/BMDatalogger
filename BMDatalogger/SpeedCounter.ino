double TimeVal = 99.99;
double BestTimeVal = 99.99;
unsigned long last_zero_time=0;
bool CheckDone = false;

void SetSpeedTime() {
  unsigned int Speed = GetVssKMH();
  
  if (Speed < 3) {
    TimeVal = 99.99;
    last_zero_time = millis();
    CheckDone = false;
  }
  if (!CheckDone) {
    if (Speed >= 3 && Speed < 100) {
      TimeVal = ((double)(((long) millis() - (long) last_zero_time)) / 1000) + 0.1;
      if (TimeVal > 20) {
        TimeVal = 99.99;
        CheckDone = true;
      }
    }
    if (Speed >= 100) {
      if (TimeVal < BestTimeVal) BestTimeVal = TimeVal;
      CheckDone = true;
    }
  }
}

double GetSpeedTime() {
  return TimeVal;
}

double GetBestSpeedTime() {
  return BestTimeVal;
}
