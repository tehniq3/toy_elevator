/*
toy elevator with 3 stations and general remote
ver.0, 1, 2 - 27.11.2018
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
}

void loop() { 

if (digitalRead(limetaj) == LOW)
{
 Serial.println("Elevator at upper floor !");
 digitalWrite(ledetaj, HIGH);
 digitalWrite(ledparter, LOW);
 digitalWrite(ledsubsol, LOW);
 localizare = 3; 
}
if (digitalRead(limparter) == LOW)
{
 Serial.println("Elevator at ground floor !");
 digitalWrite(ledetaj, LOW);
 digitalWrite(ledparter, HIGH);
 digitalWrite(ledsubsol, LOW);
 localizare = 2; 
}
if (digitalRead(limsubsol) == LOW)
{
 Serial.println("Elevator at lower floor !");
 digitalWrite(ledetaj, LOW);
 digitalWrite(ledparter, LOW);
 digitalWrite(ledsubsol, HIGH);
 localizare = 1; 
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
}
}  // end mai program
