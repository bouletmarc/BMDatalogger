const char Progbar2_START[][8] PROGMEM = {
  { B01111, B11000, B10000, B10000, B10000, B10000, B11000, B01111 },
  { B01111, B11000, B10011, B10111, B10111, B10011, B11000, B01111 }
};

const char Progbar2_MIDDLE[][8] PROGMEM = {
  { B11111, B00000, B00000, B00000, B00000, B00000, B00000, B11111 },
  { B11111, B00000, B11000, B11000, B11000, B11000, B00000, B11111 },
  { B11111, B00000, B11011, B11011, B11011, B11011, B00000, B11111 },
  { B11111, B00000, B00011, B00011, B00011, B00011, B00000, B11111 }
};

const char Progbar2_END[][8] PROGMEM = {
  { B11110, B00011, B00001, B00001, B00001, B00001, B00011, B11110 },
  { B11110, B00011, B11001, B11101, B11101, B11001, B00011, B11110 }
};

const char Progbar3[][8] PROGMEM = {
  { B10101, B00000, B00000, B00000, B00000, B00000, B00000, B10101 },
  { B10101, B10000, B10000, B10000, B10000, B10000, B10000, B10101 },
  { B10101, B10100, B10100, B10100, B10100, B10100, B10100, B10101 },
  { B10101, B10101, B10101, B10101, B10101, B10101, B10101, B10101 },
  { B10101, B00100, B00100, B00100, B00100, B00100, B00100, B10101 },
  { B10101, B00001, B00001, B00001, B00001, B00001, B00001, B10101 }
};

const char Progbar4[][8] PROGMEM = {
  { B11111, B10000, B10000, B10000, B10000, B10000, B10000, B11111 },
  { B11111, B01000, B01000, B01000, B01000, B01000, B01000, B11111 },
  { B11111, B00100, B00100, B00100, B00100, B00100, B00100, B11111 },
  { B11111, B00010, B00010, B00010, B00010, B00010, B00010, B11111 },
  { B11111, B00001, B00001, B00001, B00001, B00001, B00001, B11111 },
  { B11111, B00000, B00000, B00000, B00000, B00000, B00000, B11111 }
};

const char custom[][8] PROGMEM = {
  { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 }, // char 1 
  { 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }, // char 2 
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03 }, // char 3 
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 4 
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C, 0x18 }, // char 5 
  { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F }, // char 6 
  { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 7 
  { 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }  // char 8 
};

const char *bigChars[][2] = { 
  {"\024", "\024"}, // Space
  {"\024", "\004"}, // .
  {"\010\001\002", "\003\004\005"}, // 0
  {"\001\002", "\024\377"}, // 1
  {"\006\006\002", "\003\007\007"}, // 2
  {"\006\006\002", "\007\007\005"}, // 3
  {"\003\004\002", "\024\024\377"}, // 4
  {"\377\006\006", "\007\007\005"}, // 5
  {"\010\006\006", "\003\007\005"}, // 6
  {"\001\001\002", "\024\010\024"}, // 7
  {"\010\006\002", "\003\007\005"}, // 8
  {"\010\006\002", "\024\024\377"}, // 9
  {"\004", "\001"}, // :
  {"\010\006\002", "\377\024\377"}, // A
  {"\377\006\005", "\377\007\002"}, // B
  {"\010\001\001", "\003\004\004"}, // C
  {"\377\001\002", "\377\004\005"}, // D
  {"\377\006\006", "\377\007\007"}, // E
  {"\377\006\006", "\377\024\024"}, // F
  {"\010\001\001", "\003\004\002"}, // G
  {"\377\004\377", "\377\024\377"}, // H
  {"\001\377\001", "\004\377\004"}, // I
  {"\024\024\377", "\004\004\005"}, // J
  {"\377\004\005", "\377\024\002"}, // K
  {"\377\024\024", "\377\004\004"}, // L
  {"\010\003\005\002", "\377\024\024\377"}, // M
  {"\010\002\024\377", "\377\024\003\005"}, // N
  {"\010\001\002", "\003\004\005"}, // 0
  {"\377\006\002", "\377\024\024"}, // P
  {"\010\001\002\024", "\003\004\377\004"}, // Q
  {"\377\006\002", "\377\024\002"}, // R
  {"\010\006\006", "\007\007\005"}, // S
  {"\001\377\001", "\024\377\024"}, // T
  {"\377\024\377", "\003\004\005"}, // U
  {"\003\024\024\005", "\024\002\010\024"}, // V
  {"\377\024\024\377", "\003\010\002\005"}, // W
  {"\003\004\005", "\010\024\002"}, // X
  {"\003\004\005", "\024\377\024"}, // Y
  {"\001\006\005", "\010\007\004"}, // Z
};

byte InitMode = 99;

void CharacterInit(byte bank) {
  if (InitMode != bank) {
    uint8_t ThisArray[8];
    
    switch (bank) {
      case 0:
        for (int i=0; i<5; i++ ) {
          byte ThisByte = 0x00;
          if (ProgressBarMode == 0) {
            if (i == 0) ThisByte = 0x1F;
            if (i == 1) ThisByte = 0x10;
            if (i == 2) ThisByte = 0x18;
            if (i == 3) ThisByte = 0x1C;
            if (i == 4) ThisByte = 0x1E;
          }
          if (ProgressBarMode == 1) {
            if (i == 0) ThisByte = 0x01;
            if (i == 1) ThisByte = 0x10;
            if (i == 2) ThisByte = 0x08;
            if (i == 3) ThisByte = 0x04;
            if (i == 4) ThisByte = 0x02;
          }
          for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) ThisByte;
          lcd.createChar (i, ThisArray);
        }
        break;
        
      case 1:
        for (int i=0; i<8; i++ ) {
          for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &custom[i][i2] );
          lcd.createChar (i+1, ThisArray);
        }
        break;

      case 2:
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_START[0][i2] ); lcd.createChar (1, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_START[1][i2] ); lcd.createChar (2, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_MIDDLE[0][i2] ); lcd.createChar (3, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_MIDDLE[1][i2] ); lcd.createChar (4, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_MIDDLE[2][i2] ); lcd.createChar (5, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_END[0][i2] ); lcd.createChar (6, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_END[1][i2] ); lcd.createChar (7, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar2_MIDDLE[3][i2] ); lcd.createChar (8, ThisArray);
        break;

      case 3:
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[0][i2] ); lcd.createChar (0, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[1][i2] ); lcd.createChar (1, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[2][i2] ); lcd.createChar (2, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[3][i2] ); lcd.createChar (3, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[4][i2] ); lcd.createChar (4, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar3[5][i2] ); lcd.createChar (5, ThisArray);
        break;

      case 4:
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[0][i2] ); lcd.createChar (0, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[1][i2] ); lcd.createChar (1, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[2][i2] ); lcd.createChar (2, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[3][i2] ); lcd.createChar (3, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[4][i2] ); lcd.createChar (4, ThisArray);
        for (int i2=0; i2<8; i2++) ThisArray[i2]= (uint8_t) pgm_read_byte( &Progbar4[5][i2] ); lcd.createChar (5, ThisArray);
        break;
    }

    InitMode = bank;
  }
}


void DrawProgressBar(const int value, const int Lenght) {
  
  int percent = GetPeakPercent(value);
  DrawProgressBarPercent(percent, Lenght);
}

void DrawProgressBarPercent(const int value, const int Lenght) {
  int StyleMode = 1;
  if (ProgressBarMode == 2 | ProgressBarMode == 3) StyleMode = 2;
  if (ProgressBarMode == 4 | ProgressBarMode == 5) StyleMode = 3;
  if (ProgressBarMode == 6) StyleMode = 4;
  
  int WhiteMode = 0;
  if (ProgressBarMode == 1| ProgressBarMode == 3 | ProgressBarMode == 5) WhiteMode = 1;

  if (StyleMode == 1) CharacterInit(0);
  if (StyleMode == 2) CharacterInit(2);
  if (StyleMode == 3) CharacterInit(3);
  if (StyleMode == 4) CharacterInit(4);
  
  int percent = value;
  //int nb_columns = map(percent, 0, 100, 0, Lenght * 2 * 4 - 2 * 4);
  //int nb_columns = (percent * ((Lenght * 8) - 8)) / 100;
  int nb_columns = (percent * ((Lenght * 2) - 2)) / 100;
  double RowsNumber = ((double) Lenght / 100) * (double) percent;
  int RowsDone = 0;

  lcd.setCursor(XPos, YPos);
  
  //ProgBar Style #1
  if (StyleMode == 1) {
    if (RowsNumber >= 1) {
      for (int i=1; i < RowsNumber; i++) {
        if (WhiteMode == 0) lcd.write((uint8_t)0);
        if (WhiteMode == 1) lcd.write(' ');
        RowsDone++;
      }
    }

    RowsNumber = RowsNumber - RowsDone;
    unsigned int peace = RowsNumber * 5;
    
    switch (peace) {
      case 0:
        if (WhiteMode == 1) {
          lcd.write((uint8_t)1); 
          RowsDone++;
        }
        break;
      case 1:
        lcd.write((uint8_t)1); RowsDone++;
        break;
      case 2:
        lcd.write((uint8_t)2); RowsDone++;
        break;
      case 3:
        lcd.write((uint8_t)3); RowsDone++;
        break;
      case 4:
        lcd.write((uint8_t)4); RowsDone++;
        break;
      case 5:
        lcd.write((uint8_t)0); RowsDone++;
        break;
    }
    
    for (int i =0; i < (Lenght - RowsDone); i++) lcd.write(' ');
  }
  
  //ProgBar Style #2
  if (StyleMode == 2) {
    for (byte i = 0; i < Lenght; ++i) {
      if (i == 0) {
        if ((nb_columns > 0 && WhiteMode == 0) | (nb_columns == 1 && WhiteMode == 1)) {
          lcd.write(2);
          nb_columns -= 1;
        } else {
          lcd.write((uint8_t)1);
        }
      } else if (i == Lenght -1) {
        if (nb_columns > 0) lcd.write(7);  
        if (nb_columns == 0) lcd.write(6);
      } else {
        if ((nb_columns >= 2 && WhiteMode == 0) | (nb_columns == 2 && WhiteMode == 1)) {
          if (WhiteMode == 0) lcd.write(5);
          if (WhiteMode == 1) lcd.write(8);
          nb_columns -= 2;
        } else if (nb_columns == 1) {
          lcd.write(4);
          nb_columns -= 1;
        } else {
          lcd.write(3);
          if (WhiteMode == 1 && nb_columns > 2) nb_columns -= 2;
        }
      }
    }
  }

  //ProgBar Style #3
  if (StyleMode == 3) {
    if (RowsNumber >= 1) {
      for (int i=1; i < RowsNumber; i++) {
        if (RowsDone < Lenght - 1) {
          if (WhiteMode == 0) lcd.write((uint8_t)3);
          if (WhiteMode == 1) lcd.write((uint8_t)0);
          RowsDone++;
        }
      }
    }

    RowsNumber = RowsNumber - RowsDone;
    unsigned int peace = RowsNumber * 5;
    
    switch (peace) {
      case 0:
        if (RowsDone == 0) {
          lcd.write((uint8_t)0); RowsDone++;
        }
        break;
      case 1:
        lcd.write((uint8_t)1); RowsDone++;
        break;
      case 2:
        if (WhiteMode == 0) lcd.write((uint8_t)2);
        if (WhiteMode == 1) lcd.write((uint8_t)4);
        RowsDone++;
        break;
      case 3:
        if (WhiteMode == 0) lcd.write((uint8_t)2);
        if (WhiteMode == 1) lcd.write((uint8_t)4);
        RowsDone++;
        break;
      case 4:
        if (WhiteMode == 0) lcd.write((uint8_t)3);
        if (WhiteMode == 1) lcd.write((uint8_t)5);
        RowsDone++;
        break;
      case 5:
        if (WhiteMode == 0) lcd.write((uint8_t)3);
        if (WhiteMode == 1) lcd.write((uint8_t)5);
        RowsDone++;
        break;
    }
    
    for (int i =0; i < (Lenght - RowsDone); i++) lcd.write((uint8_t)0);
  }

  //ProgBar Style #4
  if (StyleMode == 4) {
    if (RowsNumber >= 1) {
      for (int i=1; i < RowsNumber; i++) {
        if (RowsDone < Lenght - 1) {
          lcd.write((uint8_t)5); RowsDone++;
        }
      }
    }

    RowsNumber = RowsNumber - RowsDone;
    unsigned int peace = RowsNumber * 5;
    
    switch (peace) {
      case 0:
        if (RowsDone == 0) {
          lcd.write((uint8_t)0); RowsDone++;
        }
        break;
      case 1:
        lcd.write((uint8_t)0); RowsDone++;
        break;
      case 2:
        lcd.write((uint8_t)1); RowsDone++;
        break;
      case 3:
        lcd.write((uint8_t)2); RowsDone++;
        break;
      case 4:
        lcd.write((uint8_t)3); RowsDone++;
        break;
      case 5:
        lcd.write((uint8_t)4); RowsDone++;
        break;
    }
    
    for (int i =0; i < (Lenght - RowsDone); i++) lcd.write((uint8_t)5);
  }
}

int writeBigChar(const char ch, const int x, const int y) {
  const char *(*blocks)[2] = NULL;

  if (ch < ' ' || ch > 'Z') return 0;
  if (ch >= '!' && ch <= '-') return 0;
  if (ch == '/') return 0;
  if (ch >= ';' && ch <= '@') return 0;

  int Index = (int) ch - (int) ' ';
  if (ch > '!') Index -= 13;
  if (ch > '/') Index -= 1;
  if (ch > ';') Index -= 6;
  
  blocks = &bigChars[Index];
  
  for (int half = 0; half <=1; half++) {
    int t = x;
    for (const char *cp = (*blocks)[half]; *cp; cp++) {
      if (t < 20) {
        lcd.setCursor(t, y+half);
        lcd.write(*cp);
        t = (t+1) % 40;
      }
    }
    //lcd.setCursor(t, y+half);
    //lcd.write(' ');
  }
  
  return strlen((*blocks)[0]);
}

void writeBigString(int x, int y) {
  CharacterInit(1);
  for (int i=0; i < 20; i++) {
    char c = StringBuffer[i];
    //if ((int) c != 0) x += writeBigChar(c, x, y) + 1;
    if ((int) c >= 20) x += writeBigChar(c, x, y);
    if ((int) c < 20) i += 20;
  }
}

void writeBigStringAnimated(int x, int y) {
  CharacterInit(1);
  for (int i=0; i < 20; i++) {
    char c = StringBuffer[i];
    //if ((int) c != 0) x += writeBigChar(c, x, y) + 1;
    if ((int) c >= 20) x += writeBigChar(c, x, y);
    if ((int) c < 20) i += 20;
    delay(20);
  }
}
