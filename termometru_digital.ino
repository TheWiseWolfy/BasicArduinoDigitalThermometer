/*  Name: Digital Thermometer with 7 Segment Display
 *  Author: Apetrei Bogdan
 *  Hardware:
 *  74HC595 shift register 
 *  SH5461AS 7 segment display (common catode)
 *  LM35 themperature senzor
 * Special credi goes to Carlyn Maw, Tom Igoe, David A. Mellis from Arduino for providing parts of the code for using a shift register
 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

//Choose a digit to write in the common catode 7 segment display.
const int D1 = 2;
const int D2 = 3;
const int D3 = 4;
const int D4 = 5;

//Pin for senzor LM35
int tempPin = A1;

//holders for infromation you're going to pass to shifting function
byte data;
byte dataArray[10];

//general data
float logTimer;
float cel;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  Serial.begin(9600);
  
  //Digits for the 7 Segment Display
  // DP-G-F-E-D-C-B-A
  dataArray[0] = 0x3F; //0b00111111  - 0
  dataArray[1] = 0x06; //0b00000110  - 1
  dataArray[2] = 0x5B; //0b01011011  - 2
  dataArray[3] = 0x4F; //0b01001111  - 3
  dataArray[4] = 0x66; //0b01100110  - 4
  dataArray[5] = 0x6D; //0b01101101  - 5 
  dataArray[6] = 0x7D; //0b01000000  - 6
  dataArray[7] = 0x07; //0b00000111  - 7
  dataArray[8] = 0x7F; //0b01111111  - 8 
  dataArray[9] = 0x6F; //0b01101111  - 9

  //function that blinks all the LEDs
  blinkAll_2Bytes(2,500); 
}

void loop() {
  float curentTime = millis();
  int a,b,c;
  
 //Get temperature every second
 if(curentTime > logTimer){
     float val =analogRead(tempPin);
     
     cel= constrain( (val*500)/1023 , -99,99); 
     float toDecompose = abs(cel);

     // Serial.print(cel);
     //  Serial.print("*C");
     //  Serial.println();

     //To improve 
     a = constrain( toDecompose / 10 ,0, 9) ;
     b = constrain( (int)toDecompose % 10, 0, 10);
     toDecompose *= 10;
     c = constrain( (int)toDecompose % 10, 0,10);
     logTimer = curentTime + 1000;
   }
   //Write the digits to the display, add a . to the right digit
   write3Digits(dataArray[c] ,dataArray[b]+ 0b10000000 ,dataArray[a]);
   delay(1);
}

void write3Digits(int digit1,int digit2,int digit3){
     //wirte digit 1 in D1
     
    digitalWrite(latchPin, 0); 
        shiftOut(dataPin, clockPin, digit1);  
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH); 
    digitalWrite(latchPin, 1);
    delay(1);
    
    //wirte digit 2 in D2
    digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, digit2);  
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
    digitalWrite(latchPin, 1);
    delay(1);
    
    //wirte digit 3 in D3
    digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, digit3);  
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, LOW);
        digitalWrite(D4, HIGH);
    digitalWrite(latchPin, 1);
    delay(1);

    //if that's the case, write a "-" in D4
    if(cel < 0){
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, 0b01000000);  
            digitalWrite(D1, HIGH);
            digitalWrite(D2, HIGH);
            digitalWrite(D3, HIGH);
            digitalWrite(D4, LOW);
        digitalWrite(latchPin, 1);
        delay(1);
    }
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut){
  
  // This shifts 8 bits out MSB first, on the rising edge of the clock,
  //clock idles low internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  
  //clear everything out just in case to prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    
    //if the value passed to myDataOut and a bitmask result true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    } else {  
      pinState= 0;
    }
    
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}

void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}
