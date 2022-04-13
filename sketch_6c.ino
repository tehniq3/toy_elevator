/*
toy elevator with 3 stations and general remote. 
ver.0, 1, 2 (3) - 27.11.2018
toy elevator with 6 stations and encoder
ver.4 - 15.12.2019
ver.4b - add PWM control for motor
ver.4c - display encoder position and current value on serial
ver.4d - display when elevator reach target
ver.4e - add big characters
ver.4f - change pwm frequency from 490Hz to 32kHz
ver.5 - final version, change temporary level with small characters
ver.6 - simplified version, 4 station, simple pushbuttons instead encoder

original schematic and sketch by Nicu FLORICA (niq_ro)
http://www.arduinotehniq.com/
http://nicuflorica.blogspot.com/
http://arduinotehniq.blogspot.com/
*/
#include <LiquidCrystal_I2C.h> // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // scan adress with i2c scaner sketch https://playground.arduino.cc/Main/I2cScanner

#define lim0 2  // limit switch for ground floor 
#define lim1 3  // limit switch for 1st floor
#define lim2 4  // limit switch for 2nd floor
#define lim3 7  // limit switch for 3rd floor

#define but0 8  // push button for ground floor
#define but1 9  // push button for 1st floor
#define but2 10  // push button for 2st floor
#define but3 11  // push button for 3st floor

#define sus 5   // control for lift relay (up relay)
#define jos 6   // control for lower relay (down relay)

byte pauzamica = 30;  // small pause for debugging
int pauzamare = 3000; // big pause

byte localizare = 6;   // 0 - ground, 1 - 1st floor, 2 - 2nd floor, 3 - 3rd floor, 6 - nedefinited
byte destinatie = 0;   // 0 - ground, 1 - 1st floor, 2 - 2nd floor, 3 - 3rd floor, 6 - stop
byte localizareanterioara = 7;  // value fost store previous position of elevator

void setup() {
Serial.begin(9600);

//  lcd.init(); // initialize the LCD 
   lcd.begin(); // initialize the LCD
  
  lcd.backlight(); // Turn on the blacklight and print a message.
  lcd.setCursor(0,0); 
  lcd.print(" Elevator v.6.0 ");
  lcd.setCursor(0,1);  
  lcd.print("   by niq_ro    ");
  delay(pauzamare);
 
pinMode(sus, OUTPUT);
pinMode(jos, OUTPUT);

pinMode(lim0, INPUT);
pinMode(lim1, INPUT);
pinMode(lim2, INPUT);
pinMode(lim3, INPUT);

pinMode(but0, INPUT);
pinMode(but1, INPUT);
pinMode(but2, INPUT);
pinMode(but3, INPUT);

// motor off
digitalWrite(sus, LOW);
digitalWrite(jos, LOW);

digitalWrite(lim0, HIGH);
digitalWrite(lim1, HIGH);
digitalWrite(lim2, HIGH);
digitalWrite(lim3, HIGH);

digitalWrite(but0, HIGH);
digitalWrite(but1, HIGH);
digitalWrite(but2, HIGH);
digitalWrite(but3, HIGH);

lcd.clear();
}

void loop() { 

if (digitalRead(lim0) == LOW)
{
 localizare = 0; 
 if (localizareanterioara != localizare) // initial was !=
 {
 Serial.println("Elevator at ground floor !");
 lcd.setCursor(0,0);
 lcd.print("Lift la parter. ");
 }
}

if (digitalRead(lim1) == LOW)
{
  localizare = 1; 
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 1st floor !");
 lcd.setCursor(0,0);
 lcd.print("Lift la etajul 1");
 }
 localizare = 1; 
}

if (digitalRead(lim2) == LOW)
{
   localizare = 2;
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 2nd floor !");
 lcd.setCursor(0,0);
 lcd.print("Lift la etajul 2");
 }
 localizare = 2; 
}

if (digitalRead(lim3) == LOW)
{
   localizare = 3; 
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 3rd floor !");
 lcd.setCursor(0,0);
 lcd.print("Lift la etajul 3");
 }
}

// read buttons
if (digitalRead(but0) == LOW)
{
  destinatie = 0;
  delay(pauzamica);    
    Serial.print("destination is ");
    Serial.println("ground."); 
 lcd.setCursor(15,1);
 lcd.print("P");
    }

if (digitalRead(but1) == LOW)
{    
   destinatie = 1;
   delay(pauzamica);    
    Serial.print("destination is ");
    Serial.println("1st floor."); 
 lcd.setCursor(15,1);
 lcd.print("1");
}

if (digitalRead(but2) == LOW)
{
    destinatie = 2;
    delay(pauzamica);    
    Serial.print("destination is ");
    Serial.println("2nd floor."); 
 lcd.setCursor(15,1);
 lcd.print("2");
    }  

 if (digitalRead(but3) == LOW)
{
    destinatie = 3;
    delay(pauzamica);    
    Serial.print("destination is ");
    Serial.println("3rd floor."); 
 lcd.setCursor(15,1);
 lcd.print("3");
}

if (destinatie > localizare) // must goes up
{
 Serial.println("Elevator goes up !");
 digitalWrite(sus, HIGH);
 digitalWrite(jos, LOW);
 lcd.setCursor(0,1);
 lcd.print("Liftul urca !  ");
}

if (destinatie < localizare) // must goes down
{
 Serial.println("Elevator goes down !");
 digitalWrite(sus, LOW);
 digitalWrite(jos, HIGH);
 lcd.setCursor(0,1);
 lcd.print("Liftul coboara!");
}

if (destinatie == localizare) // must stop
{
 Serial.println("Elevator stops !");
 digitalWrite(sus, LOW);
 digitalWrite(jos, LOW);
 delay(1000);
 lcd.setCursor(0,1);
 lcd.print("Lift oprit !   ");
}

localizareanterioara = localizare;
delay(pauzamica); // rest break
}  // end mai program
