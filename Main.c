#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// Screen Resolution
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// You can use any (4 or) 5 pins
#define SCLK_PIN 11
#define MOSI_PIN 12
#define DC_PIN   9
#define CS_PIN   10
#define RST_PIN  8 // Optional

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

int MenuTracker = 0;
/* 
 0 - Main Menu
 1 - Tic Tac Toe
 11 - TTT Game
*/

String TTTBoard[3][3] = {
  {" ", " ", " "},
  {" ", " ", " "},
  {" ", " ", " "}
};

bool TTTGameOn = false;
int TTTInput;
int TTTTurn = 0;    // 0 - O & 1 - X

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte RowPins[4] = {A7, A6, A5, A4};
byte ColPins[4] = {A3, A2, A1, A0};

Keypad keypad = Keypad(makeKeymap(keys), RowPins, ColPins, 4, 4);

bool toggleOled = false;

void ToggleOled()
{
  if (toggleOled)
  {
    Serial.println("Oled has turned off!");
    toggleOled = false;
    oled.fillRect(0, 0, 128, 128, BLACK);
    TTTGameOn = false;
  }
  else if (!toggleOled)
  {
    Serial.println("Oled has turned on!");
    MenuTracker = 0;
    toggleOled = true;
    TTTGameOn = false;
  }
}

void Menus()
{
  if (MenuTracker == 0)
  {
    TTTGameOn = false;
    oled.fillRect(0, 0, 128, 128, BLACK);
    oled.setTextColor(WHITE);
    oled.setCursor(16, 0);
    oled.println("Press the number");
    oled.setCursor(14, 8);
    oled.println("to play the game!");
    oled.setCursor(0, 24);
    oled.setTextColor(MAGENTA);
    oled.println("\n   1 - Tic Tac Toe");
    oled.setCursor(0, 44);
    oled.setTextColor(YELLOW);
    oled.println("    2 - Ping Pong");
    MenuTracker = -1;
  }
  else if (MenuTracker == 1)
  {
    TTTGameOn = false;
    oled.fillRect(0, 0, 128, 128, BLACK);
    oled.setTextColor(WHITE);
    oled.setCursor(29, 0);
    oled.println("Tic Tac Toe");
    oled.setCursor(0, 24);
    oled.setTextColor(0x07E3);
    oled.println("\n       1 - 1v1");
    oled.setCursor(0, 44);
    oled.setTextColor(0xFEC0);
    oled.println("    2 - Bot (Easy)");
    oled.setCursor(0, 54);
    oled.setTextColor(0xFAE0);
    oled.println("    4 - Bot (Hard)");
    oled.setCursor(0, 100);
    oled.setTextColor(0x94B2);
    oled.println("     # - Go Back");
    MenuTracker = -2;
  }
  else if (MenuTracker == 11)
  {
    while (TTTGameOn) {
      oled.fillRect(0, 0, 128, 64, BLACK);
      oled.setTextColor(WHITE);
      oled.setCursor(29, 0);
      oled.println("Tic Tac Toe");
      oled.setCursor(45, 24);
      oled.println(TTTBoard[0][0] + "|" + TTTBoard[0][1] + "|" + TTTBoard[0][2]);
      oled.setCursor(45, 32);
      oled.println("-+-+-");
      oled.setCursor(45, 40);
      oled.println(TTTBoard[1][0] + "|" + TTTBoard[1][1] + "|" + TTTBoard[1][2]);
      oled.setCursor(45, 48);
      oled.println("-+-+-");
      oled.setCursor(45, 56);
      oled.println(TTTBoard[2][0] + "|" + TTTBoard[2][1] + "|" + TTTBoard[2][2]);
      
      if (TTTTurn == 0 && TTTInput == 1 && TTTBoard[0][0] == " ")
      {
        TTTBoard[0][0] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 2 && TTTBoard[0][1] == " ")
      {
        TTTBoard[0][1] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 3 && TTTBoard[0][2] == " ")
      {
        TTTBoard[0][2] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 4 && TTTBoard[1][0] == " ")
      {
        TTTBoard[1][0] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 5 && TTTBoard[1][1] == " ")
      {
        TTTBoard[1][1] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 6 && TTTBoard[1][2] == " ")
      {
        TTTBoard[1][2] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 7 && TTTBoard[2][0] == " ")
      {
        TTTBoard[2][0] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 8 && TTTBoard[2][1] == " ")
      {
        TTTBoard[2][1] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 0 && TTTInput == 9 && TTTBoard[2][2] == " ")
      {
        TTTBoard[2][2] = "O";
        TTTTurn = 1;
      }
      else if (TTTTurn == 1 && TTTInput == 1 && TTTBoard[0][0] == " ")
      {
        TTTBoard[0][0] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 2 && TTTBoard[0][1] == " ")
      {
        TTTBoard[0][1] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 3 && TTTBoard[0][2] == " ")
      {
        TTTBoard[0][2] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 4 && TTTBoard[1][0] == " ")
      {
        TTTBoard[1][0] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 5 && TTTBoard[1][1] == " ")
      {
        TTTBoard[1][1] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 6 && TTTBoard[1][2] == " ")
      {
        TTTBoard[1][2] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 7 && TTTBoard[2][0] == " ")
      {
        TTTBoard[2][0] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 8 && TTTBoard[2][1] == " ")
      {
        TTTBoard[2][1] = "X";
        TTTTurn = 0;
      }
      else if (TTTTurn == 1 && TTTInput == 9 && TTTBoard[2][2] == " ")
      {
        TTTBoard[2][2] = "X";
        TTTTurn = 0;
      }
      
      delay(200);
    }
  }
}

void MenuChecker()
{
  if (MenuTracker == -1)
  {
    MenuTracker = 1;
  }
  else if (MenuTracker == -2)
  {
    TTTGameOn = true;
    MenuTracker = 11;
  }
}

void TTTInputCheck(int num)
{
  if (MenuTracker == 11 && num == 1)
  {
    TTTInput = 1;
  }
  else if (MenuTracker == 11 && num == 2)
  {
    TTTInput = 2;
  }
  else if (MenuTracker == 11 && num == 3)
  {
    TTTInput = 3;
  }
  else if (MenuTracker == 11 && num == 4)
  {
    TTTInput = 4;
  }
  else if (MenuTracker == 11 && num == 5)
  {
    TTTInput = 5;
  }
  else if (MenuTracker == 11 && num == 6)
  {
    TTTInput = 6;
  }
  else if (MenuTracker == 11 && num == 7)
  {
    TTTInput = 7;
  }
  else if (MenuTracker == 11 && num == 8)
  {
    TTTInput = 8;
  }
  else if (MenuTracker == 11 && num == 9)
  {
    TTTInput = 9;
  }
}

void CheckKey()
{
  char key = keypad.getKey();

  switch (key)
  {
    case '*':
      Serial.println("Pressed: *");
      ToggleOled();
      break;
    case '#':
      MenuTracker = 0;
      Serial.println("Pressed: #");
      break;
    case 'A':
      Serial.println("Pressed: A");
      break;
    case 'B':
      Serial.println("Pressed: B");
      break;
    case 'C':
      Serial.println("Pressed: C");
      break;
    case 'D':
      Serial.println("Pressed: D");
      break;
    case '0':
      Serial.println("Pressed: 0");
      break;
    case '1':
      Serial.println("Pressed: 1");
      TTTInputCheck(1);
      MenuChecker();
      break;
    case '2':
      Serial.println("Pressed: 2");
      TTTInputCheck(2);
      break;
    case '3':
      Serial.println("Pressed: 3");
      TTTInputCheck(3);
      break;
    case '4':
      Serial.println("Pressed: 4");
      TTTInputCheck(4);
      break;
    case '5':
      Serial.println("Pressed: 5");
      TTTInputCheck(5);
      break;
    case '6':
      Serial.println("Pressed: 6");
      TTTInputCheck(6);
      break;
    case '7':
      Serial.println("Pressed: 7");
      TTTInputCheck(7);
      break;
    case '8':
      Serial.println("Pressed: 8");
      TTTInputCheck(8);
      break;
    case '9':
      Serial.println("Pressed: 9");
      TTTInputCheck(9);
      break;
  }
  delay(100);
}


void setup()
{
  Serial.begin(9600);
  Serial.println("Serial has started!");

  oled.begin();
  Serial.println("Oled has started!");
}

void loop()
{
  CheckKey();
  Menus();
}
