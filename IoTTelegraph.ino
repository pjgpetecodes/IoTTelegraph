/**
 * Telegraph Setup
 */
#define LEDPin 16;
#define telegraphPin 5;

int telegraphActive = false;
int telegraphWasPressed = false;
int pulseOnLength = 0;
int pulseStartTime = 0;
int pulseEndTime = 0;
int pulseOffLength = 0;
String code = "";


void setup() {
    // put your setup code here, to run once:
    pinMode(LEDPin, OUTPUT);
    pinMode(telegraphPin, INPUT);
    Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
    // put your main code here, to run repeatedly:

    int telegraphState = digitalRead(telegraphPin);

    if (telegraphState == LOW)
    {
        digitalWrite(LEDPin, LOW);
        
        if (telegraphActive == true)
        {
          telegraphActive = false;
          pulseEndTime = millis();
          //Serial.print("Pulse End: ");
          //Serial.print(pulseEndTime);
            
          pulseOnLength = pulseEndTime - pulseStartTime;
          
          if (pulseOnLength > 50)
          {
            //Serial.print("Valid Pulse Length");
            //Serial.println();        // carriage return after the last label
            //Serial.print("Pulse Length: ");
            //Serial.print(signalLength);
            //Serial.println();        // carriage return after the last label

            if (pulseOnLength > 50 && pulseOnLength < 200)
            {
              code += ".";
              //Serial.print(".");
              telegraphWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else if (pulseOnLength >= 200 && pulseOnLength < 500)
            {
              code += "-";
              //Serial.print("-");
              telegraphWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else
            {
              // Do nothing
            }
                        
          }          
        }
        else if (telegraphWasPressed == true)
        {

          if (millis() - pulseEndTime > 300)
          {
            converter(code);
            code = "";                            //reset code to blank string
            telegraphWasPressed = false;
          }
          
        }
      }
      else
      {
          digitalWrite(LEDPin, HIGH);
  
          if (telegraphActive == false)
          {
              pulseStartTime = millis();
              telegraphActive = true;
              //Serial.print("Pulse Start: ");
              //Serial.print(pulseStartTime);
              //Serial.println();        // carriage return after the last label
              
          }
      }
}

void converter(String code) {

  /*

  Morse Code Table:
  -----------------

  A   . -           N   - .         0   - - - - -
  B   - . . .       O   - - -       1   . - - - -
  C   - . - .       P   . - - .     2   . . - - -
  D   - . .         Q   - - . -     3   . . . - -
  E   .             R   . - .       4   . . . . -
  F   . . - .       S   . . .       5   . . . . .
  G   - - .         T   -           6   - . . . .
  H   . . . .       U   . . -       7   - - . . .
  I   . .           V   . . . -     8   - - - . .
  J   . - - -       W   . - -       9   - - - - .
  K   - . -         X   - . . -
  L   . - . .       Y   - . - - 
  M   - -           Z   - - . .
  
  Send Message    . - . - . -
  Cancel Message  . . . . . .

  */

  /* Based on Converter code here... https://www.instructables.com/id/Morse-Code-Decoder/  */

  static String letters[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",".-.", 
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", 
                              "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", 
                              "E"
                            };
  int i = 0;

  if (code == ".-.-.-")
  {
    Serial.println(".");        //for break
  }
  else
  {
    while (letters[i] != "E")  //loop for comparing input code with letters array
    {
      if (letters[i] == code)
      {
        //
        // If we're on letters...
        //
        if (i < 24)
        {
          Serial.print(char('A' + i));  
        }
        else
        {
          Serial.print(char('A' + i-43));
        }
        
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.print("Unknown Code:");  //if input code doesn't match any letter, error
    }
  }
  
}
