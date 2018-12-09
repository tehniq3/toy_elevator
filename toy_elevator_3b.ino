/*
toy elevator with 3 stations and general remote
ver.0, 1, 2 - 27.11.2018
ver.3, 3b - 09.12.2018 (add 7 segment led display with common cathode or common anode)
original schematic and sketch by Nicu FLORICA (niq_ro)
http://www.arduinotehniq.com/
http://nicuflorica.blogspot.com/
http://arduinotehniq.blogspot.com/
*/

#define limetaj 2  // limit switch for upper floor
#define limparter 3  // limit switch for ground floor
#define limsubsol 4  // limit switch for lower floor

#define sus 5   // control for lift relay
#define jos 6   // control for lower relay

#define cometaj 7    // switch for upper floor
#define comparter 8  // switch for ground floor
#define comsubsol 9  // switch for lower floor 

#define ledetaj 11 //10    // led for upper floor
#define ledparter 12 //11  // led for ground floor
#define ledsubsol 13  //12  // led for lower floor 

int pauzamica = 150;  // small pause for debugging

byte localizare = 4;   // 3 - upper floor, 2 - ground floor, 1 - lower floor, 4 - nedefinited
byte destinatie = 0;   // 3 - upper floor, 2 - ground floor, 1 - lower floor, 0 - stop


byte digitArray[12][7] =  // {a,b,c,d,e,f,g}
 { 
 { 1,1,1,1,1,1,0 }, // = 0
 { 0,1,1,0,0,0,0 }, // = 1
 { 1,1,0,1,1,0,1 }, // = 2
 { 1,1,1,1,0,0,1 }, // = 3
 { 0,1,1,0,0,1,1 }, // = 4
 { 1,0,1,1,0,1,1 }, // = 5
 { 1,0,1,1,1,1,1 }, // = 6
 { 1,1,1,0,0,0,0 }, // = 7
 { 1,1,1,1,1,1,1 }, // = 8
 { 1,1,1,0,0,1,1 }, // = 9
 { 0,0,0,0,0,0,0 }, // = off
 { 1,1,0,0,1,1,1 } // = P
 };

#define sega 14 // A0
#define segb 15 // A1
#define segc 16 // A2
#define segd 17 // A3
#define sege 18 // A4
#define segf 19 // A5
#define segg 10

//byte tip = 0;  // for common cathode
 byte tip = 1;  // for common anode

void setup() {
Serial.begin(9600);
  
pinMode(sus, OUTPUT);
pinMode(jos, OUTPUT);
pinMode(limetaj, INPUT);
pinMode(limparter, INPUT);
pinMode(limsubsol, INPUT);
pinMode(cometaj, INPUT);
pinMode(comparter, INPUT);
pinMode(comsubsol, INPUT);
pinMode(ledetaj, OUTPUT);
pinMode(ledparter, OUTPUT);
pinMode(ledsubsol, OUTPUT);

digitalWrite(sus, LOW);
digitalWrite(jos, LOW);
digitalWrite(limetaj, HIGH);
digitalWrite(limparter, HIGH);
digitalWrite(limsubsol, HIGH);
digitalWrite(cometaj, HIGH);
digitalWrite(comparter, HIGH);
digitalWrite(comsubsol, HIGH);
digitalWrite(ledetaj, LOW);
digitalWrite(ledparter, LOW);
digitalWrite(ledsubsol, LOW);

pinMode(sega, OUTPUT); // kingbrigth - a
pinMode(segb, OUTPUT); // kingbrigth - b
pinMode(segc, OUTPUT); // kingbrigth - c
pinMode(segd, OUTPUT); // kingbrigth - d
pinMode(sege, OUTPUT); // kingbrigth - e
pinMode(segf, OUTPUT); // kingbrigth - f
pinMode(segg, OUTPUT); // kingbrigth - g

digitalWrite(sega, LOW);
digitalWrite(segb, LOW);
digitalWrite(segc, LOW);
digitalWrite(segd, LOW);
digitalWrite(sege, LOW);
digitalWrite(segf, LOW);
digitalWrite(segg, LOW);
}

void loop() { 

if (digitalRead(limetaj) == LOW)
{
 Serial.println("Elevator at upper floor !");
 digitalWrite(ledetaj, HIGH);
 digitalWrite(ledparter, LOW);
 digitalWrite(ledsubsol, LOW);
 localizare = 3; 
if (tip == 0) setDigit0(2);  // display 2
else setDigit1(2);  // display 2
}

if (digitalRead(limparter) == LOW)
{
Serial.println("Elevator at ground floor !");
 digitalWrite(ledetaj, LOW);
 digitalWrite(ledparter, HIGH);
 digitalWrite(ledsubsol, LOW);
 localizare = 2;  
 if (tip == 0) setDigit0(1);  // display 1
 else setDigit1(1);  // display 1

}
if (digitalRead(limsubsol) == LOW)
{
 Serial.println("Elevator at lower floor !");
 digitalWrite(ledetaj, LOW);
 digitalWrite(ledparter, LOW);
 digitalWrite(ledsubsol, HIGH);
 localizare = 1;
 if (tip == 0) setDigit0(11);  // display P on common cathode
 else setDigit1(11);  // display P on common anode
 /*
 if (tip == 0) setDigit0(0);  // display 0 on common cathode
 else setDigit1(0);  // display 0 on common anode
 */
}
  if (digitalRead(cometaj) == LOW)  // if is push the button for upper floor
  {
    destinatie = 3;
    delay(pauzamica);
  }
  
  if (digitalRead(comparter) == LOW)  // if is push the button for ground floor
  {
    destinatie = 2;
    delay(pauzamica);
  }
  
  if ((destinatie == 2) and (localizare == 3))
  {
  destinatie = 21;
  }
  if ((destinatie == 2) and (localizare == 1))
  {
  destinatie = 23;
  }

  
  if (digitalRead(comsubsol) == LOW)  // if is push the button for lower floor
  {
    destinatie = 1;
    delay(pauzamica);
  }

if (destinatie == 3) 
{
  if (digitalRead(limetaj) == HIGH)
  {
    digitalWrite(sus, HIGH);
    digitalWrite(jos, LOW);
  }  
  else   // destination is reached
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, LOW);
    destinatie = 0;
    localizare = 3;
  }
}

if (destinatie == 1) 
{
  if (digitalRead(limsubsol) == HIGH)
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, HIGH);
  }  
  else  // destination is reached
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, LOW);
    destinatie = 0;
    localizare = 1;
  }
}

if (destinatie == 23) 
{
  if (digitalRead(limparter) == HIGH)
  {
    digitalWrite(sus, HIGH);
    digitalWrite(jos, LOW);
  }  
  else   // destination is reached
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, LOW);
    destinatie = 0;
    localizare = 2;
  }
}

if (destinatie == 21) 
{
  if (digitalRead(limparter) == HIGH)
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, HIGH);
  }  
  else  // destination is reached
  {
    digitalWrite(sus, LOW);
    digitalWrite(jos, LOW);
    destinatie = 0;
    localizare = 2;
  }
}

if (localizare > 3)
{
  digitalWrite(ledetaj, LOW);
digitalWrite(ledparter, LOW);
digitalWrite(ledsubsol, LOW); 
if (tip == 0) setDigit0(10);    // display off on common cathode
else setDigit1(10);    // display off on common anode
}

}  // end mai program


// we define a function to display one digit  on common cathode
void setDigit0(byte digit) 
{
 digitalWrite(sega, digitArray[digit][0]);
 digitalWrite(segb, digitArray[digit][1]);
 digitalWrite(segc, digitArray[digit][2]);
 digitalWrite(segd, digitArray[digit][3]);
 digitalWrite(sege, digitArray[digit][4]);
 digitalWrite(segf, digitArray[digit][5]);
 digitalWrite(segg, digitArray[digit][6]);
}

// we define a function to display one digit on common anode
void setDigit1(byte digit) 
{
 digitalWrite(sega, 1-digitArray[digit][0]);
 digitalWrite(segb, 1-digitArray[digit][1]);
 digitalWrite(segc, 1-digitArray[digit][2]);
 digitalWrite(segd, 1-digitArray[digit][3]);
 digitalWrite(sege, 1-digitArray[digit][4]);
 digitalWrite(segf, 1-digitArray[digit][5]);
 digitalWrite(segg, 1-digitArray[digit][6]);
}
