#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

int startbutton=(A3);
int stopbutton=(A2);
int starter=(2);
int run=(3);
int runing=(4);
int oilpress=(5);
int pwrfail=(6);
int pwrnml=(7);
int nmrlind=(8);
int pwrfind=(9);
int tfrsw=(10);

String cmd = String("STOP");
String status = String("STANDBY");
String autocmd = String("A");

void setup() {
    // Inintal LCD set up
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GENERATOR CONTROLER");
  lcd.setCursor(2, 1);
  lcd.print("VER. DEC 2024");

  pinMode(startbutton, INPUT);
  pinMode(stopbutton, INPUT_PULLUP);
  pinMode(starter, OUTPUT);
  pinMode(run, OUTPUT);
  pinMode(runing, INPUT_PULLUP);
  pinMode(oilpress, INPUT_PULLUP);
  pinMode(pwrfail, INPUT_PULLUP);
  pinMode(nmrlind, OUTPUT);
  pinMode(pwrnml, INPUT_PULLUP);
  pinMode(pwrfind, OUTPUT);
  pinMode(tfrsw, OUTPUT);

  delay(3000);

 lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("GEN STATUS:");
  lcd.setCursor(0, 1);
  lcd.print("COMMAND:");

  digitalWrite(pwrfind, LOW);
  digitalWrite(nmrlind, HIGH);

}

void loop() {



  lcd.setCursor(12, 0);
  lcd.print(status);
  lcd.setCursor(9, 1);
  lcd.print(cmd);

  if (digitalRead(startbutton) == LOW  && digitalRead(runing) == HIGH)
{
  cmd = "START";
  status = "PENDING";
  digitalWrite(run, HIGH);
  digitalWrite(pwrfind, HIGH);
  lcd.setCursor(1, 2);
  lcd.print("MANUAL START");
}
if (digitalRead(pwrfail) == LOW && digitalRead(runing) == HIGH)
{
  cmd = "START";
  status = "PENDING";
  digitalWrite(run, HIGH);
  lcd.setCursor(1, 2);
  lcd.print("AUTO START  ");
  delay(10);
  digitalWrite(pwrfind, HIGH);
  digitalWrite(nmrlind, LOW);
}

if (cmd == "START")
{
digitalWrite(starter, HIGH);
}else digitalWrite(starter, LOW);

if (digitalRead(runing) == LOW)
{
  cmd = "RUN  ";
  status = "RUNNING  ";
  digitalWrite(starter, LOW);
} 

if (digitalRead(runing) == HIGH && digitalRead(run) == HIGH)
{
  cmd = "START";
  status = "FAILURE";
}

if (digitalRead(stopbutton) == LOW )
{
  cmd = "STOP ";
  status = "STANDBY ";
  digitalWrite(run, LOW);
  digitalWrite(nmrlind, LOW);
  digitalWrite(pwrfind, LOW);
  digitalWrite(nmrlind, HIGH);
  lcd.setCursor(1, 2);
  lcd.print("MANUAL STOP   ");
}

if (digitalRead(pwrnml) == LOW)
{
  cmd = "STOP ";
  status = "STANDBY ";
  digitalWrite(run, LOW);
  digitalWrite(nmrlind, LOW);
  digitalWrite(pwrfind, LOW);
  digitalWrite(nmrlind, HIGH);
  lcd.setCursor(1, 2);
  lcd.print("AUTO STOP    ");
}

if (digitalRead(oilpress) == LOW && digitalRead(run) == HIGH && digitalRead(starter) == LOW)
{
  status = "OIL PRES";
  cmd = "STOP";
  digitalWrite(run, LOW);
} 

if (digitalRead(runing) == LOW && digitalRead(run) == HIGH)
{
  digitalWrite(tfrsw, HIGH);
  lcd.setCursor(1, 3);
  lcd.print("LOAD ON GEN ");
} else 
 {
  digitalWrite(tfrsw, LOW);
  lcd.setCursor(1, 3);
  lcd.print("LOAD OFF GEN");
 }


}
