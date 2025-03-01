bool menuSetupDone = false;
bool menuSelectedGame = false;
byte menuCurSelection = 0;
int menuLoopFrames = 0;

typedef struct {
  uint8_t menuNum;
  char* gameTitle;
  int* gameColorRED;
  int* gameColorGREEN;
  int* gameColorBLUE;
} menuGames;

const menuGames menuItems[] {
  {0, "Snake", 170,167,204},
  {1, "Pong", 228,188,97},
  {2, "Flappy", 39, 176, 214},
  {3, "Draw", 115,190,115},
  {4, "2048", 230,223,185},
  {5, "Simon", 236,140,140},
  {6, "Dino", 255,192,77},
  {7, "Joke", 255,217,210}
};


void menu_reset() {
  menuSetupDone = false;
  menuSelectedGame = false;
  menuCurSelection = 0;
  menuLoopFrames = 0;  
}

int menu_centerScore(int score) {
  return 52 - (score > 9 ? (score > 99 ? 17.5 : 7.5) : 0);
}

int menu_centerTitleAdd(int length) {
  return (-9 * length) + 65;
}

void menu_draw() {
  for (int i = 0; i < 8; i++) {
    lcd.setColor(menuItems[i].gameColorRED, menuItems[i].gameColorGREEN, menuItems[i].gameColorBLUE);
    lcd.setBackColor(menuItems[i].gameColorRED, menuItems[i].gameColorGREEN, menuItems[i].gameColorBLUE);
    lcd.setFont(BigFont);
    if (i >= 0 && i <= 3) {
      lcd.fillRect(i * 120, 28, 120 + (i * 120), 174);
      lcd.setColor(0, 0, 0);
      lcd.print(menuItems[i].gameTitle, i * 120 + menu_centerTitleAdd(strlen(menuItems[i].gameTitle)), 40);
      if (i == 0) {
        lcd.print(String(EEPROM.read("SNAKE_HIGHSCORE")), i * 120 + menu_centerScore(EEPROM.read("SNAKE_HIGHSCORE")), 143);
        lcd.drawBitmap(28, 62, 32, 32, snake_logo, 2);
      } else if (i == 1) {
        lcd.print(String(EEPROM.read("PONG_HIGHSCORE")), i * 120 + menu_centerScore(EEPROM.read("PONG_HIGHSCORE")), 143);
        lcd.drawBitmap(148, 62, 32, 32, pong_logo, 2);
      } else if (i == 2) {
        lcd.print(String(EEPROM.read("FLAPPY_HIGHSCORE")), i * 120 + menu_centerScore(EEPROM.read("FLAPPY_HIGHSCORE")), 143);
        lcd.drawBitmap(270, 58, 20, 20, bird, 3);
      } else if (i == 3) {        
        lcd.print("NONE", i * 120 + 29.5, 143);  
        lcd.drawBitmap(388, 62, 32, 32, draw_logo, 2);
      }
      lcd.setFont(SmallFont);
      lcd.print("HIGH SCORE:", i * 120 + 21, 130);
      lcd.drawLine(i * 120 + 11, 57, 120 + (i * 120) - 11, 57);
    }
    if (i >= 4 && i <= 7) {
      lcd.fillRect((i - 4) * 120, 174, 120 + ((i - 4) * 120), 320);
      lcd.setColor(0, 0, 0);
      lcd.print(menuItems[i].gameTitle, (i - 4) * 120 + menu_centerTitleAdd(strlen(menuItems[i].gameTitle)), 186);
      if (i == 4) {
        lcd.drawBitmap(28, 208, 32, 32, num_logo, 2);
        int score = (int)pow(2, EEPROM.read("X2048_HIGHSCORE")); if (score != 2) {score++;} else {score=0;}
        if(score == 2) {score=0;}
        lcd.print(String(score), (i - 4) * 120 + menu_centerScore(score), 289);                
      } else if (i == 5) {        
        lcd.drawBitmap(148, 210, 32, 32, simon_logo, 2);
        lcd.print(String(EEPROM.read("SIMON_HIGHSCORE")), (i - 4) * 120 + menu_centerScore(EEPROM.read("SIMON_HIGHSCORE")), 289);
      } else if (i == 6) {        
        lcd.drawBitmap(278, 210, 15, 19, dino_logo, 3);    
        lcd.print(String(EEPROM.read("DINO_HIGHSCORE")), (i - 4) * 120 + menu_centerScore(EEPROM.read("DINO_HIGHSCORE")), 289);
      } else if (i == 7) {        
        lcd.drawBitmap(387, 207, 32, 32, laughingEmoji_logo, 2);
        lcd.print("NONE", (i - 4) * 120 + 29.5, 289);
      }
      lcd.setFont(SmallFont);
      lcd.print("HIGH SCORE:", (i - 4) * 120 + 21, 276);
      lcd.drawLine((i - 4) * 120 + 11, 203, 120 + ((i - 4) * 120) - 11, 203);
    }
  }
}

void menu_drawThickRect(int R, int G, int B, int x1, int y1, int x2, int y2) {
  lcd.setColor(R, G, B);
  lcd.drawRect(x1, y1, x2, y2);
  lcd.drawRect(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
  lcd.drawRect(x1 + 2, y1 + 2, x2 - 2, y2 - 2);
}

void print_top() {
  lcd.setColor(255, 255, 255);
  lcd.setBackColor(32, 32, 32);
  lcd.setFont(BigFont);
  // lcd.print("Innokit Game Console: " + String(readPercent()) + "%", CENTER, 5);  
  lcd.print("Innokit Game Console: 100%", CENTER, 5);  
}

void menu_setup() {
  lcd.setColor(32, 32, 32);
  lcd.fillRect(0, 0, 480, 28);
  print_top();
  menu_draw();
  menu_drawThickRect(0, 0, 0, menuCurSelection * 120, 28, 120 + (menuCurSelection * 120), 174);
  menuSetupDone = true;
}

void menu_selectorHighlight(bool transparent) {
  if (!transparent) {
    if (menuCurSelection >= 0 && menuCurSelection <= 3) {
      menu_drawThickRect(24,24,24, menuCurSelection * 120, 28, 120 + (menuCurSelection * 120), 174);
    }
    if (menuCurSelection >= 4 && menuCurSelection <= 7) {
      menu_drawThickRect(24,24,24, (menuCurSelection - 4) * 120, 174, 120 + ((menuCurSelection - 4) * 120), 320);
    }
  } else {
    if (menuCurSelection >= 0 && menuCurSelection <= 3) {
      menu_drawThickRect(menuItems[menuCurSelection].gameColorRED, menuItems[menuCurSelection].gameColorGREEN, menuItems[menuCurSelection].gameColorBLUE, menuCurSelection * 120, 28, 120 + (menuCurSelection * 120), 174);
    }
    if (menuCurSelection >= 4 && menuCurSelection <= 7) {
      menu_drawThickRect(menuItems[menuCurSelection].gameColorRED, menuItems[menuCurSelection].gameColorGREEN, menuItems[menuCurSelection].gameColorBLUE, (menuCurSelection - 4) * 120, 174, 120 + ((menuCurSelection - 4) * 120), 320);
    }
  }
}

void menu_loop() {
  if (!menuSetupDone) {
    lcd.clrScr();
    menu_setup();
  }
  if (move == JoystickMove::None) {
    if (menuLoopFrames == 0) {
      menu_selectorHighlight(false);
    }
    if (menuLoopFrames == 600) {
      menu_selectorHighlight(true);
      print_top();
    }
    menuLoopFrames++;
    if (menuLoopFrames >= 1200) {
      menuLoopFrames = 0;
    }
  } else {
    if (move != JoystickMove::None) {
      menu_selectorHighlight(true);
      if (move == JoystickMove::Left || move == JoystickMove::UpLeft || move == JoystickMove::DownLeft) {
        if (menuCurSelection > 0) {
          menuCurSelection--;
        } else {
          menuCurSelection = 7;
        }
      }
      if (move == JoystickMove::Right || move == JoystickMove::UpRight || move == JoystickMove::DownRight) {
        if (menuCurSelection < 7) {
          menuCurSelection++;
        } else {
          menuCurSelection = 0;
        }
      }
      if (move == JoystickMove::Down || move == JoystickMove::Up) {
        if (menuCurSelection > 3) {
          menuCurSelection = menuCurSelection - 4;
        } else {
          menuCurSelection = menuCurSelection + 4;
        }
      }
      menuLoopFrames = 0;
      menu_selectorHighlight(false);
      delay(300);
    }
  }
  if (digitalRead(ButtonH) == LOW) {
    if (!menuSelectedGame) {
      lcd.setBackColor(0, 0, 0);
      lcd.clrScr();
      if (menuCurSelection == 0) {
        gameRunning = SNAKE;
      } else if (menuCurSelection == 1) {
        gameRunning = PONG;
      } else if (menuCurSelection == 2) {
        gameRunning = FLAPPY;
      } else if (menuCurSelection == 3) {
        gameRunning = DRAWING;
      } else if (menuCurSelection == 4) {
        gameRunning = X2048;
      } else if (menuCurSelection == 5) {
        gameRunning = SIMON;
      } else if (menuCurSelection == 6) {
        gameRunning = DINO;
      } else if (menuCurSelection == 7) {
        gameRunning = JOKE;
      }
      menuSelectedGame = true;
    }
  }
}
