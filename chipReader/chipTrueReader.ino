// Assume boardVdd is connected to Vdd on the Arduino
// Assume boardGND is connected to GND on the Arduino
// output1t  -->  PIN2
// output2t  -->  PIN3
// output3t  -->  PIN4
// output4t  -->  PIN5
// output5t  -->  PIN6
// output6t  -->  PIN7
// output7t  -->  PIN8
// output8t  -->  PIN9
// output1f  -->  PIN10
// output2f  -->  PIN11
// output3f  -->  PIN12
// output4f  -->  PIN13
// output5f  -->  PINA0
// output6f  -->  PINA1
// output7f  -->  PINA2
// output8f  -->  PINA3
// outputa   -->  PINA4

// Flip boolean if a character is read. Await two rails
// going LOW on a single bit before setting this to true again
bool awaitingNextChar = true;

// The reader has no idea how long it takes the chip to process the raised ack rail
int delayTime = 200;

// Set pins as input to read the output of the chip
void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, INPUT);

  mappedWrite("outputa", LOW);

  // Print read encrypted characters into serial
  Serial.begin(9600);
}

// This function makes it easy to change pin assignments in the future.
// It maps an output name to a particular pin that is outlined in the
// beginning of this program
int mappedRead(String pinName) {
  if (pinName.equals("output1t")) {
    return digitalRead(2);
  }
  else if (pinName.equals("output2t")) {
     return digitalRead(3);
  }
  else if (pinName.equals("output3t")) {
     return digitalRead(4);
  }
  else if (pinName.equals("output4t")) {
     return digitalRead(5);
  }
  else if (pinName.equals("output5t")) {
     return digitalRead(6);
  }
  else if (pinName.equals("output6t")) {
     return digitalRead(7);
  }
  else if (pinName.equals("output7t")) {
     return digitalRead(8);
  }
  else if (pinName.equals("output8t")) {
     return digitalRead(9);
  }
  else if (pinName.equals("output1f")) {
     return digitalRead(10);
  }
  else if (pinName.equals("output2f")) {
     return digitalRead(11);
  }
  else if (pinName.equals("output3f")) {
     return digitalRead(12);
  }
  else if (pinName.equals("output4f")) {
     return digitalRead(13);
  }
  else if (pinName.equals("output5f")) {
     return digitalRead(A0);
  }
  else if (pinName.equals("output6f")) {
     return digitalRead(A1);
  }
  else if (pinName.equals("output7f")) {
     return digitalRead(A2);
  }
  else if (pinName.equals("output8f")) {
     return digitalRead(A3);
  }
}

void mappedWrite(String pinName, int writeVal) {
  if (pinName.equals("outputa")) {
    digitalWrite(A4, writeVal);
  }
}

// Read each pairs of pins. Determine if a signal is present (assume two cannot
// be HIGH at the same time). A signal is present when one of the pair of signals
// is high. If any pair is LOW LOW, then we return -1
int getChar() {
  // Use bitshift manipulations to capture the character represented by the pin signals
  int runningTotal = 0;
  for (int i = 1; i <= 8; i++) {
    switch(i) {
      case 1:
        if (mappedRead("output1t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        // If this case goes through, both signals were low so we return -1
        else if (mappedRead("output1f") == LOW) {
          return -1;
        }
        // If we reach here, then the false rail was HIGH. This does not add
        // anything to the character we are reading, so we are done
        break;
      case 2:
        if (mappedRead("output2t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output2f") == LOW) {
          return -1;
        }
        break;
      case 3:
        if (mappedRead("output3t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output3f") == LOW) {
          return -1;
        }
        break;
      case 4:
        if (mappedRead("output4t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output4f") == LOW) {
          return -1;
        }
        break;
      case 5:
        if (mappedRead("output5t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output5f") == LOW) {
          return -1;
        }
        break;
      case 6:
        if (mappedRead("output6t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output6f") == LOW) {
          return -1;
        }
        break;
      case 7:
        if (mappedRead("output7t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output7f") == LOW) {
          return -1;
        }
        break;
      case 8:
        if (mappedRead("output8t") == HIGH) {
          runningTotal += (1 << (i - 1));
        }
        else if (mappedRead("output8f") == LOW) {
          return -1;
        }
        break;
    }
  }
  // Return the character we just read if we reach here (each pair of rails is defined)
  return runningTotal;
}

void debug() {

  String output1t = String(digitalRead(2));
  String output2t = String(digitalRead(3));
  String output3t = String(digitalRead(4));
  String output4t = String(digitalRead(5));
  String output5t = String(digitalRead(6));
  String output6t = String(digitalRead(7));
  String output7t = String(digitalRead(8));
  String output8t = String(digitalRead(9));
  String output1f = String(digitalRead(10));
  String output2f = String(digitalRead(11));
  String output3f = String(digitalRead(12));
  String output4f = String(digitalRead(13));
  String output5f = String(digitalRead(A0));
  String output6f = String(digitalRead(A1));
  String output7f = String(digitalRead(A2));
  String output8f = String(digitalRead(A3));

  Serial.println("output1t: " + output1t);
  Serial.println("output2t: " + output2t);
  Serial.println("output3t: " + output3t);
  Serial.println("output4t: " + output4t);
  Serial.println("output5t: " + output5t);
  Serial.println("output6t: " + output6t);
  Serial.println("output7t: " + output7t);
  Serial.println("output8t: " + output8t);
  Serial.println("output1f: " + output1f);
  Serial.println("output2f: " + output2f);
  Serial.println("output3f: " + output3f);
  Serial.println("output4f: " + output4f);
  Serial.println("output5f: " + output5f);
  Serial.println("output6f: " + output6f);
  Serial.println("output7f: " + output7f);
  Serial.println("output8f: " + output8f);
}

// Do the following forever
void loop() {
  // Get the character if any
  int charVal = getChar();
  debug();
  // If we are waiting for a character and we get something that is not -1, we print it
  if (awaitingNextChar && charVal >= 0) {
    char myChar = (char) charVal;
    Serial.print("I read the following character: ");
    Serial.println(myChar);

    mappedWrite("outputa", HIGH);
    awaitingNextChar = false;
  }
  // If the output rails have reset and we are not waiting for a new character, then change the state
  // such that we are waiting for a new character once again
  else if (!awaitingNextChar && charVal == -1) {
    mappedWrite("outputa", LOW);
    awaitingNextChar = true;
  }
}
