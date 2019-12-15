/*
toy elevator with 3 stations and general remote. 
ver.0, 1, 2 (3) - 27.11.2018
toy elevator with 6 stations and encoder
ver.4 - 15.12.2019
original schematic and sketch by Nicu FLORICA (niq_ro)
http://www.arduinotehniq.com/
http://nicuflorica.blogspot.com/
http://arduinotehniq.blogspot.com/
*/
#include <LiquidCrystal_I2C.h> // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 4);  // scan adress with i2c scaner sketch https://playground.arduino.cc/Main/I2cScanner

#include <Encoder.h> // from http://www.pjrc.com/teensy/td_libs_Encoder.html
#define knob1 2  // pin1 for encoder
#define knob2 3  // pin2 for encoder
#define knobsw 4 // switch for encoder

Encoder knob(knob1, knob2); //encoder connected to pins 2 and 3 (and ground)
int knobval; // value for the rotation of the knob

#define lim0 5  // limit switch for ground floor 
#define lim1 6  // limit switch for 1st floor
#define lim2 7  // limit switch for 2nd floor
#define lim3 8  // limit switch for 3rd floor
#define lim4 9  // limit switch for 4th floor
#define lim5 10 // limit switch for 5th floor (last floor)

#define sus 11   // control for lift relay (up relay)
#define jos 12   // control for lower relay (down relay)

#define acspin A0 // pin for read current through circuit
float amp = 0;
int acs = 0;  // instant value of ADC at ACS712
int acsm = 0; // value for made amount of ADC values for more readings
float amps = 0.0;  // value of current
float amps2 = 0.0; // store value for current for previuos measurement
float acs0 = 512.0;  // usual ADC value at ACS712 without current is 1024/2 = 512.0
float ampsmax = 5.0; // vaxim value for current

byte pauzamica = 30;  // small pause for debugging
byte pauzasupermica = 2; // very small pause for read ACS sensor
int pauzamare = 5000; // big pause for emergency situations (overcurrent, blocking, etc)

byte localizare = 6;   // 0 - ground, 1 - 1st floor, 2 - 2nd floor, 3 - 3rd floor, 4 - 4th floor, 5 - 5th floor, 6 - nedefinited
byte destinatie = 0;   // 0 - ground, 1 - 1st floor, 2 - 2nd floor, 3 - 3rd floor, 4 - 4th floor, 5 - 5th floor, 6 - stop
int destinatietemp = 0;    // value selected using encoder 
byte localizareanterioara = 6;  // value fost store previous position of elevator

void setup() {
Serial.begin(9600);

  lcd.begin(); // initialize the LCD 
  lcd.backlight(); // Turn on the blacklight and print a message.
  lcd.setCursor(0,0); 
  lcd.print("Toy Elevator 4.a");
  lcd.setCursor(0,1);  
  lcd.print("by niq_ro & Tom");
  delay(pauzamare);
 
pinMode(sus, OUTPUT);
pinMode(jos, OUTPUT);

pinMode(lim0, INPUT);
pinMode(lim1, INPUT);
pinMode(lim2, INPUT);
pinMode(lim3, INPUT);
pinMode(lim5, INPUT);
pinMode(lim5, INPUT);

pinMode(knobsw, INPUT);

// motor off
digitalWrite(sus, LOW);
digitalWrite(jos, LOW);

digitalWrite(lim0, HIGH);
digitalWrite(lim1, HIGH);
digitalWrite(lim2, HIGH);
digitalWrite(lim3, HIGH);
digitalWrite(lim4, HIGH);
digitalWrite(lim5, HIGH);

digitalWrite(knobsw, HIGH);
}

void loop() { 

if (digitalRead(lim0) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at ground floor !");
 lcd.setCursor(0,0); 
 lcd.print("Lift la parter !");
 }
 localizare = 0; 
}

if (digitalRead(lim1) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 1st floor !");
 lcd.setCursor(0,0); 
 lcd.print("Lift la etaj 1 !");
 }
 localizare = 1; 
}

if (digitalRead(lim2) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 2nd floor !");
 lcd.setCursor(0,0); 
 lcd.print("Lift la etaj 2 !");
 }
 localizare = 2; 
}

if (digitalRead(lim3) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 3rd floor !");
 lcd.setCursor(0,0); 
 lcd.print("Lift la etaj 3 !");
 }
 localizare = 3; 
}

if (digitalRead(lim4) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 4th floor !");
 lcd.setCursor(0,0); 
 lcd.print("Lift la etaj 4 !");
 }
 localizare = 4; 
}

if (digitalRead(lim5) == LOW)
{
 if (localizareanterioara != localizare)
 {
 Serial.println("Elevator at 5th floor !");
  lcd.setCursor(0,0); 
 lcd.print("Lift la heliport");
 }
 localizare = 5; 
}

localizareanterioara = localizare;

if (destinatie > localizare) // must goes up
{
 Serial.println("Elevator goes up !");
 digitalWrite(sus, HIGH);
 digitalWrite(jos, LOW);
}

if (destinatie < localizare) // must goes down
{
 Serial.println("Elevator goes down !");
 digitalWrite(sus, LOW);
 digitalWrite(jos, HIGH);
}

if (destinatie == localizare) // must stop
{
 Serial.println("Elevator stops !");
 digitalWrite(sus, LOW);
 digitalWrite(jos, LOW);
}

// read encoder
    knob.write(0);
    delay (pauzamica);
    knobval = knob.read();
    if (knobval < -1) {
      knobval = -1;
    }
    if (knobval > 1) {
      knobval = 1;
    }
    destinatietemp = destinatietemp + knobval;
    if (destinatietemp < 0) 
    {
      destinatietemp = 0;
    }
    if (destinatietemp > 5) {
      destinatietemp = 5;
    }
   if (digitalRead(knobsw) == LOW)
   {
    destinatie = destinatietemp;
    Serial.print("New destination is ");
    if (destinatie == 0)
    {
    Serial.println("ground."); 
    lcd.setCursor(0,1); 
    lcd.print("Lift spre parter");
    }
    if (destinatie == 1)
    {
    Serial.println("1st floor."); 
    lcd.setCursor(0,1); 
    lcd.print("Lift spre etaj 1");
    }
    if (destinatie == 2)
    {
    Serial.println("2nd floor."); 
    lcd.setCursor(0,1); 
    lcd.print("Lift spre etaj 2");
    }   
    if (destinatie == 3)
    {
    Serial.println("3rd floor."); 
    lcd.setCursor(0,1); 
    lcd.print("Lift spre etaj 3");
    }
    if (destinatie == 4)
    {
    Serial.println("4th floor."); 
    lcd.setCursor(0,1); 
    lcd.print("Lift spre etaj 4");
    }
    if (destinatie == 5)
    {
    Serial.println("las floor."); 
    lcd.setCursor(0,1); 
    lcd.print("Spre heliport ! ");
    }     
    delay(pauzamica);
   }   

// read ACS712-05 sensor 10 times to be more accurate value of current
 acsm = 0;  
 for (byte i = 0; i < 10; i++) 
  {
 acs = analogRead(acspin);  // read sensor
 delay(pauzasupermica);
 acsm = acsm + acs;
  }
 amp = (float)acsm/10.;
 amps = (float)((acs0 - amp) * 5.0 / 1024.0 / 0.185);  // asc712-05 -> 185mV/A, ACS712-20 -> 100mV/A, ACS712-30 -> 66mV/A
 if (amps < 0) amps = -amps;
 amps2 = amps;  

if (amps > ampsmax)
{
 Serial.println("Elevator stops (overcurrent) !");
 digitalWrite(sus, LOW);
 digitalWrite(jos, LOW);
 lcd.clear();
 lcd.setCursor(0,0); 
 lcd.print("Lift oprit! STOP");
 delay(pauzamare);
}
 

//delay(pauzamica); // rest break
}  // end mai program
