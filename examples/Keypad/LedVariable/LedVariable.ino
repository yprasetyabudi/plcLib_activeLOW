/* Programmable Logic Controller Library for the Arduino and Compatibles

   Matrix Keypad with Latched Outputs Using Output to Pins and Variables

   Arduino Uno Pin Connections:
   Input X0 - unused (Arduino pin A0)
   Input X1 - unused (Arduino pin A1)
   Input X2 - unused (Arduino pin A2)
   Input X3 - unused (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)
   
   4X3 Matrix Keypad Connections:
   ROW1 - Arduino pin 8
   ROW2 - Arduino pin 7
   ROW3 - Arduino pin 4
   ROW4 - Arduino pin 2
   COL1 - Arduino pin 12
   COL2 - Arduino pin 11
   COL3 - Arduino pin 10

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

#include <Keypad.h>    // Include the Keypad library
#include <plcLib.h>    // Include the plcLib library

unsigned int AUX0 = 0; // Variable used to hold keypad latch output

char keyPress = 0;     // Holds the currently pressed key value (if any)
const byte ROWS = 4;   // Keypad has four rows
const byte COLS = 3;   // Keypad has three columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 8, 7, 4, 2 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 11, 10 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  setupPLC();                 // Define input / output pins
}

void loop()
{
  keyPress = kpd.getKey();    // Read key pressed (if any)
  
  latchKey('1', '2', AUX0);   // Keyboard latch, Set = '1', Reset = '2',
                              // output to variable AUX0
  
  in(AUX0);                   // Read variable AUX0
  out(Y0);                    // Output to pin Y0


  latchKey('3', '4', Y1);     // Keyboard latch, Set = '3', Reset = '4',
                              // output = Y1 (pin 5)
}

// Keypad-based Set-Reset latch, outputting to a pin.
unsigned int latchKey(char en, char dis, int outPin) {
  if(keyPress) {
    if (keyPress == en) {
      digitalWrite(outPin, HIGH);
    }
    if (keyPress == dis) {
      digitalWrite(outPin, LOW);
    }
  } 
}

// Keypad-based Set-Reset latch, outputting to a variable.
unsigned int latchKey(char en, char dis, unsigned int &outVar) {
  if(keyPress) {
    if (keyPress == en) {
      outVar = 1;
    }
    if (keyPress == dis) {
      outVar = 0;
    }
  } 
}