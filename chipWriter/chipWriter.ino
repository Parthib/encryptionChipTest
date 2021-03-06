// Assume boardVdd is connected to Vdd on the Arduino
// Assume boardGND is connected to GND on the Arduino
// Assume boardReset is connected to A5 on the Arduino
// Assume outputa is connected to A4 on the Arduino
// cf       -->  PIN0
// ct       -->  PIN1
// input1t  -->  PIN2
// input2t  -->  PIN3
// input3t  -->  PIN4
// input4t  -->  PIN5
// input5t  -->  PIN6
// input6t  -->  PIN7
// input7t  -->  PIN8
// input8t  -->  PIN9
// input1f  -->  PIN10
// input2f  -->  PIN11
// input3f  -->  PIN12
// input4f  -->  PIN13
// input5f  -->  PINA0
// input6f  -->  PINA1
// input7f  -->  PINA2
// input8f  -->  PINA3

// The delay is equivalent to the simulate "s" line of irsim
int delayTime = 200;

// Set everything to output so that we can
// input characters/seeds/acks into the Arduino
void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  // Reset everything using the global reset signal
  hardReset();

  // Set the seed
  setSeed(255);

  // Write this string to the chip
  writeString("Hello World!");
}

// Like a soft reset except also work with the board reset signal and reset the outputa signal
void hardReset() {
  mappedWrite("boardReset", HIGH);
  
  mappedWrite("outputa", LOW);

  softReset();

  mappedWrite("boardReset", LOW);

  delay(delayTime);
}

// Reset everything to low
void softReset() {
    mappedWrite("ct", LOW);
    mappedWrite("cf", LOW);
    mappedWrite("input1t", LOW);
    mappedWrite("input1f", LOW);
    mappedWrite("input2t", LOW);
    mappedWrite("input2f", LOW);
    mappedWrite("input3t", LOW);
    mappedWrite("input3f", LOW);
    mappedWrite("input4t", LOW);
    mappedWrite("input4f", LOW);
    mappedWrite("input5t", LOW);
    mappedWrite("input5f", LOW);
    mappedWrite("input6t", LOW);
    mappedWrite("input6f", LOW);
    mappedWrite("input7t", LOW);
    mappedWrite("input7f", LOW);
    mappedWrite("input8t", LOW);
    mappedWrite("input8f", LOW);

    delay(delayTime);
}

// Write things to the input dual rails
void setInput(int valToWrite) {
  // Opposite value to save to the false rail

  // Set the pins to the seed value
  for (int i = 1; i <= 8; i++) {
    // Bitwise AND select of the seed value at the bit position
    int setVal = (1 << (i - 1)) & valToWrite;
    // Opposite value to save to the false rail
    int oppVal = (setVal == 1) ? 0 : 1;

    switch(i) {
      case 1:
        mappedWrite("input1t", setVal);
        mappedWrite("input1f", oppVal);
        break;
      case 2:
        mappedWrite("input2t", setVal);
        mappedWrite("input2f", oppVal);
        break;
      case 3:
        mappedWrite("input3t", setVal);
        mappedWrite("input3f", oppVal);
        break;
      case 4:
        mappedWrite("input4t", setVal);
        mappedWrite("input4f", oppVal);
        break;
      case 5:
        mappedWrite("input5t", setVal);
        mappedWrite("input5f", oppVal);
        break;
      case 6:
        mappedWrite("input6t", setVal);
        mappedWrite("input6f", oppVal);
        break;
      case 7:
        mappedWrite("input7t", setVal);
        mappedWrite("input7f", oppVal);
        break;
      case 8:
        mappedWrite("input8t", setVal);
        mappedWrite("input8f", oppVal);
        break;  
    }
  }
}

// The max seed value is 255. Arguments greater than this will just wrap around by mod 256)
void setSeed(int seedVal) {
  // When ct is set to true, the chip saves the seed value
  mappedWrite("ct", HIGH);
  mappedWrite("cf", LOW);

  // Set the input rails to the seed value
  setInput(seedVal);

  delay(delayTime);

  // Set everything to low
  softReset();
}

// Like the setSeed function except we enable the cf rail and we have to cast the character
void writeCharacter(char letter) {
  // Cast the character
  int setVal = (int) letter;

  // Enable cf to encrypt character
  mappedWrite("ct", LOW);
  mappedWrite("cf", HIGH);

  // Set the input rails
  setInput(setVal);

  delay(delayTime);

  // Set everything to low
  softReset();

  delay(delayTime);

  // Handshake with output rail so we can proceed with another character. Technically the second
  // Arduino should do this, but I cannot think of a good way to handle handshakes using the second Arduino
  mappedWrite("outputa", HIGH);
  delay(delayTime);
  mappedWrite("outputa", LOW);
  delay(delayTime);
}

// Loop over the characters of a string and apply the writeCharacter function to it.
void writeString(String myString) {
  for (int i = 0; i < myString.length(); i++) {
    writeCharacter(myString[i]);
  }
}

// This function makes it easy to change pin assignments in the future.
// It maps an input name to a particular pin that is outlined in the 
// beginning of this program
void mappedWrite(String pinName, int writeVal) {
  if (pinName.equals("cf")) {
    digitalWrite(0, writeVal);
  }
  else if (pinName.equals("ct")) {
    digitalWrite(1, writeVal);
  }
  else if (pinName.equals("input1t")) {
    digitalWrite(2, writeVal);
  }
  else if (pinName.equals("input2t")) {
     digitalWrite(3, writeVal);
  }
  else if (pinName.equals("input3t")) {
     digitalWrite(4, writeVal);
  }
  else if (pinName.equals("input4t")) {
     digitalWrite(5, writeVal);
  }
  else if (pinName.equals("input5t")) {
     digitalWrite(6, writeVal);
  }
  else if (pinName.equals("input6t")) {
     digitalWrite(7, writeVal);
  }
  else if (pinName.equals("input7t")) {
     digitalWrite(8, writeVal);
  }
  else if (pinName.equals("input8t")) {
     digitalWrite(9, writeVal);
  }
  else if (pinName.equals("input1f")) {
     digitalWrite(10, writeVal);
  }
  else if (pinName.equals("input2f")) {
     digitalWrite(11, writeVal);
  }
  else if (pinName.equals("input3f")) {
     digitalWrite(12, writeVal);
  }
  else if (pinName.equals("input4f")) {
     digitalWrite(13, writeVal);
  }
  else if (pinName.equals("input5f")) {
     digitalWrite(A0, writeVal);
  }
  else if (pinName.equals("input6f")) {
     digitalWrite(A1, writeVal);
  }
  else if (pinName.equals("input7f")) {
     digitalWrite(A2, writeVal);
  }
  else if (pinName.equals("input8f")) {
     digitalWrite(A3, writeVal);
  }
  else if (pinName.equals("outputa")) {
     digitalWrite(A4, writeVal);
  }
  else if (pinName.equals("boardReset")) {
     digitalWrite(A5, writeVal);
  }
}

// The write Arduino needs to be sequential unless you want to endlessly encrypt data
void loop() {

}
