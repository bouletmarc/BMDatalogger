bool IsWarning = false;

void GetWarnings() {
  bool Warning = false;
  if (EngineRunning) {
    if (GetRpm() > Warning_RPM) Warning = true;
    if (GetIat() > Warning_IAT) Warning = true;
    if (GetEct() > Warning_ECT) Warning = true;
  
    //Disable (not warning)
    if (!Warning && IsWarning) {
      //lcd.backlight();
      backlight();
      IsWarning = false;
    }
  
    //Warning (Trigger Flash)
    if (Warning) {
      if (!IsWarning) {
        //lcd.noBacklight();
        noBacklight();
        IsWarning = true;
      }
      else {
        //lcd.backlight();
        backlight();
        IsWarning = false;
      }
    }
  }
}
