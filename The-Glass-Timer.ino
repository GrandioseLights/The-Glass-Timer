
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

String text1 = "The_Glass_Timer ";
String text2 = " Timer          ";
int app  = 0; //App Switch
int menu = 0; //main menu selector
int timu = 0; //timer menu selector
int clock = 0; //Clock menu selector
int settg = 0; //Settings Menu Selector

int percent = 0; // Controlls the LEDs, if enables.

int h = 0;
int m = 0;
int s = 0;

int hl = 0;
int ml = 0;
int sl = 0;

bool led_on = true;

void refresh(int d = 100)
{
  lcd.clear();
  lcd.print(text1);
  lcd.setCursor(0, 2);
  lcd.print(text2);
  delay(d);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  refresh();//initial refresh
}

void loop()
{
  int up = analogRead(A0);
  int down = analogRead(A1);
  int left = analogRead(A2);
  int right = analogRead(A3);
  int enter = analogRead(A5);

  if (h > 60) {
    h = 60;
  }
  if (m > 60) {
    m = 60;
  }
  if (h > 60) {
    s = 60;
  }

  if (h < 0) {
    h = 0;
  }
  if (m < 0) {
    m = 0;
  }
  if (s < 0) {
    s = 0;
  }
  Serial.print(hl + " ");
  Serial.print(ml + " ");
  Serial.println(sl);

  if (up == 1023 || down == 1023 || left == 1023 || right == 1023 || enter == 1023){refresh();}else{delay(10);refresh();}//Refresh screen only when an input is recieved, or every 10ms
  switch (app) {
    case 0:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      switch (menu) {
        case 0:
          text1 = "The_Glass_Timer ";
          text2 = " Timer          ";
          if (down == 1023) {
            menu++;
            break;
          }
          break;
        case 1:
          text1 = "The_Glass_Timer ";
          text2 = ">Timer<         ";
          if (up == 1023) {
            menu--;
            break;
          } else if (down == 1023) {
            menu++;
            break;
          } else if (enter == 1023) {
            app = 1;
            break;
          }
          break;
        case 2:
          text1 = ">Settings<      ";
          text2 = " Credits        ";
          if (up == 1023) {
            menu--;
            break;
          } else if (down == 1023) {
            menu++;
            break;
          } else if (enter == 1023) {
            app = 2;
            break;
          }
          break;
        case 3:
          text1 = " Settings       ";
          text2 = ">Credits<       ";
          if (up == 1023) {
            menu--;
            break;
          } else if (enter == 1023) {
            app = 3;
            break;
          }
          break;
      }
      break;
    case 1: // The user has selected the Timer application
      switch (timu) {
        case 0:
          text1 = "Timer      Back ";
          text2 = ">" + String(h) + " Hours<" + m + "m " + s + "s Start";
          if (up == 1023) {
            h++;
            break;
          } else if (down == 1023) {
            h--;
            break;
          } else if (right == 1023) {
            timu++;
            break;
          }
          break;
        case 1:
          text1 = "Timer      Back ";
          text2 = " " + String(h) + "h>" + m + " Minutes<" + s + "s Start";
          if (up == 1023) {
            m++;
            break;
          } else if (down == 1023) {
            m--;
            break;
          } else if (left == 1023) {
            timu--;
            break;
          } else if (right == 1023) {
            timu++;
            break;
          }
          break;
        case 2:
          text1 = "Timer      Back ";
          text2 = String(h) + "h " + m + "m>" + s + " Seconds<Start";
          if (up == 1023) {
            s++;
            break;
          } else if (down == 1023) {
            s--;
            break;
          } else if (left == 1023) {
            timu--;
            break;
          } else if (right == 1023) {
            timu++;
            break;
          }
          break;
        case 3:
          text1 = "Timer      Back ";
          text2 = String(h) + "h " + m + "m " + s + "s>Start<";
          hl = h;
          ml = m;
          sl = s;
          if (up == 1023) {
            timu++;
            break;
          } else if (left == 1023) {
            timu--;
            break;
          } else if (enter == 1023) {
            timu = 5;
            break;
          }
          break;
        case 4:
          text1 = "Timer     >Back<";
          text2 = String(h) + "h " + m + "m " + s + "s Start";
          if (down == 1023) {
            timu--;
            break;
          } else if (enter == 1023) {
            app = 0;
            break;
          }
          break;
        case 5:
          switch (clock) {
            case 0:
              text1 = " Restart  >Back<";
              text2 = String(hl) + ": " + ml + ": " + round(sl);
              if (left == 1023) {
  
                clock++;
                break;
              } else if (enter == 1023) {
  
                timu = 3;
                break;
              }
              break;
            case 1:
              text1 = " >Restart< Back ";
              text2 = String(hl) + ": " + ml + ": " + round(sl);
              if (right == 1023) {
  
                clock--;
                break;
              } else if (enter == 1023) {
  
                hl = h;
                ml = m;
                sl = s;
                digitalWrite(8, LOW);
                digitalWrite(9, LOW);
                digitalWrite(10, LOW);
                digitalWrite(11, LOW);
                digitalWrite(12, LOW);
                digitalWrite(13, LOW);
                break;
              }
              if (sl < 0) {
                if (ml < 0) {
                  if (hl != 0) {
                    ml = 59;
                  } else {
                    ml = 0;
                  }
                  hl--;
                }
                if (hl != 0 || ml != 0) {
                  sl = 59;
                } else {
                  sl = 0;
                }
                ml--;
              }
              sl = sl - 0.01;

              if (led_on) {
                percent = (hl / 60  - h / 60) + (ml / 60 - m / 60) + (sl / 60 - s / 60) / 3;
                if (percent < 6 / 6) {
                  digitalWrite(8, HIGH);
                }
                if (percent < 5 / 6) {
                  digitalWrite(9, HIGH);
                }
                if (percent < 4 / 6) {
                  digitalWrite(10, HIGH);
                }
                if (percent < 3 / 6) {
                  digitalWrite(11, HIGH);
                }
                if (percent < 2 / 6) {
                  digitalWrite(12, HIGH);
                }
                if (percent < 1 / 6) {
                  digitalWrite(13, HIGH);
                }
              }
              break;
          }
          break;
      }
      break;
    case 2: // The user has selected the settings Screen
      switch (settg) {
        case 0:
          text1 = "          >Back<";
          text2 = " LEDs on?     " + String(led_on);
          if (down == 1023) {
            settg++;
            break;
          } else if (enter == 1023) {
            app = 0;
            break;
          }
          break;
        case 1:
          text1 = "           Back ";
          text2 = ">LEDs on?<     " + String(led_on);
          if (up == 1023) {
            settg--;
            break;
          } else if (down == 1023) {
            settg++;
            break;
          } else if (enter == 1023) {
            led_on = !led_on;
            break;
          }
          break;
        case 2:
          text1 = ">Placeholder<   ";
          text2 = "                ";
          if (up == 1023) {
            settg--;
            break;
          }
          break;
      }
      break;
    case 3: // The user has selected the Credits screen
      text1 = "CREDITS 1/3     ";
      text2 = "Coding: Zachary ";
      refresh(); delay(3000);

      text1 = "CREDITS 2/3     ";
      text2 = "Libraries: ARDUI";
      refresh(); delay(1000);
      text2 = "ibraries: ARDUIN";
      refresh(); delay(500);
      text2 = "braries: ARDUINO";
      refresh(); delay(1000);

      text2 = "Libraries: ARDUI";
      refresh(); delay(500);
      text2 = "ibraries: ARDUIN";
      refresh(); delay(500);
      text2 = "braries: ARDUINO";
      refresh(); delay(1000);

      text1 = "CREDITS 3/3     ";
      text2 = "James: James    ";
      refresh(); delay(3000);

      app = 0;
      break;
  }
}
