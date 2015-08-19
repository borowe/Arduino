/*
 * matrixMpx sketch
 * Sequence LEDs starting from first column and row until all LEDS are lit
 * Multiplexing is used to control 64 LEDs with 16 pins
 */

const int columnPins[] = { 2, 3, 4, 5, 6, 7, 8, 9};
const int rowPins[]   = { 10,11,12,15,16,17,18,19};

int pixel       = 0;        // 0 to 63 LEDs in the matrix
int columnLevel = 0;        // pixel value converted into LED column
int rowLevel    = 0;        // pixel value converted into LED row

void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(columnPins[i], OUTPUT);  // make all the LED pins outputs
    pinMode(rowPins[i], OUTPUT);
  }
}

void loop() {
  pixel = pixel + 1;
  if(pixel > 63)
     pixel = 0;

  columnLevel = pixel / 8;                     // map to the number of columns
  rowLevel = pixel % 8;                        // get the fractional value
  for (int column = 0; column < 8; column++)
  {
    digitalWrite(columnPins[column], LOW);     // connect this column to Ground
    for(int row = 0; row < 8; row++)
    {
      if (columnLevel > column)
      {
        digitalWrite(rowPins[row], HIGH);  // connect all LEDs in row to +5 volts
      }
      else if (columnLevel == column && rowLevel >= row)
      {
          digitalWrite(rowPins[row], HIGH);
      }
      else
      {
        digitalWrite(columnPins[column], LOW); // turn off all LEDs in this row
      }
      delayMicroseconds(300);     // delay gives frame time of 20ms for 64 LEDs
      digitalWrite(rowPins[row], LOW);         // turn off LED
    }

    digitalWrite(columnPins[column], HIGH);   // disconnect this column from GND
  }
}
      
    
