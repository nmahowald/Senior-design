#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <Filters.h>
LiquidCrystal_I2C lcd(0x27,20,4);
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
int analogPin = A3;
float val = 0.0000;
float voltage = 5.000;
float bits = 1024;

float divisor = 2.9355;
float adder = 95.893;
int loops = 16;
int interrupt2 = 0;

float filterFrequency = 5.0;

  FilterOnePole lowpassFilter(LOWPASS, filterFrequency);
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  //FilterOnePole lowpassFilter(LOWPASS, filterFrequency);
  lcd.init();
   lcd.init();
   lcd.backlight();
   Serial.begin(9600); 
     delay(3000);
   
     Serial.println("Ready");
}
////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void loop(){
digitalWrite(ledPin, state);
wait();

//return 0;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
void wait(){
  if(interrupt2 == 1){
    Serial.println("1");
     noInterrupts();
    Serial.println("Interrupts Off");
    math();
    lcd_print();
  }
//  else if(interrupt2 == 2){
//    Serial.println("2");
//  }
//  else if(interrupt2 == 3){
//        Serial.println("3");
//
//  }
//  else if(interrupt2 == 4){
//       Serial.println("4");
//  }
//  else if(interrupt2 == 5){
//    noInterrupts();
//    Serial.println("interruptsOff");
//    math();
//        Serial.println("5");

//  }
  else(interrupt2=0);

}
///////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
void blink() {

  state = !state;
  interrupt2++;
  val = lowpassFilter.input(analogRead(A3));
//  Serial.println(val);
//delay(1);
//  val = val + analogRead(A3);
//  delay(1);
//  val = val + analogRead(A3);
//  delay(1);
//  val = val + analogRead(A3);
//  delay(1);
//  val = val + analogRead(A3);
//  delay(1);
  }
////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//void math(){
////  val = (5000*val)/bits;//Turns the signal to mV
////  Serial.println(val,5);
////  val = (val + adder)/(divisor);// From mV to Amps
//  val = (((val/5*5000/2.997) + adder)/(divisor*bits))/loops;//signal to amps
//  Serial.print("Final Magnitude:");
//  Serial.println(val);
//  interrupt2 = 0;
//  //lcd_print();
//  interrupts();
//  Serial.println("Interrupts On");
//}
/////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
void lcd_print(){
  lcd.setCursor(0,0);   //MASTER: A CKT: 1
  lcd.print("MASTER: ");//0123456789012345
  lcd.print("X");//Phase of master A, B, C
  lcd.setCursor(10,0);
  lcd.print("CKT: ");
  lcd.print("X");//circuit number master is on1,2
  lcd.setCursor(0,1);//MAG: XXXA PHASE: XXX
  lcd.print("MAG: "); //012345678901234567890
  lcd.print("XXX");// Current on master
  lcd.setCursor(8,1);
  lcd.print("A PHASE: ");
  lcd.print("XXX");//phase of master
  lcd.setCursor(0,2);      //REFERENCE: X CKT: X
  lcd.print("REFERENCE: ");//012345678901234567890
  lcd.print("X");//phase of reference A,B,C
  lcd.setCursor(13,2);
  lcd.print("CKT: ");
  lcd.print("X");//circuit of reference 1,2
  lcd.setCursor(0,3);//MAG: XXXA PHASE: XXX
  lcd.print("MAG: "); //012345678901234567890
  lcd.print("XXX");// Current on reference
  lcd.setCursor(8,3);
  lcd.print("A PHASE: ");
  lcd.print("XXX");//phase of reference
  
}
//////////////////////////////////////////////////////////////////
