const int LEDPin = BUILTIN_LED;
const int buttonPin = 5;
int buttonPressed = false;
int buttonWasPressed = false;
int pulseOnLength = 0;
int pulseStartTime = 0;
int pulseEndTime = 0;
int pulseOffLength = 0;
String code = "";


void setup() {
    // put your setup code here, to run once:
    pinMode(LEDPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
    // put your main code here, to run repeatedly:

    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW)
    {
        digitalWrite(LEDPin, LOW);
        
        if (buttonPressed == true)
        {
          buttonPressed = false;
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
              buttonWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else if (pulseOnLength >= 200 && pulseOnLength < 500)
            {
              code += "-";
              //Serial.print("-");
              buttonWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else
            {
              // Do nothing
            }
                        
          }          
        }
        else if (buttonWasPressed == true)
        {

          if (millis() - pulseEndTime > 300)
          {
            convertor(code);
            code = "";                            //reset code to blank string
            buttonWasPressed = false;
          }
          
        }
      }
      else
      {
          digitalWrite(LEDPin, HIGH);
  
          if (buttonPressed == false)
          {
              pulseStartTime = millis();
              buttonPressed = true;
              //Serial.print("Pulse Start: ");
              //Serial.print(pulseStartTime);
              //Serial.println();        // carriage return after the last label
              
          }
      }
}

void convertor(String code) {
  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "E"
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
      Serial.println("<Wrong input>");  //if input code doesn't match any letter, error
    }
  }
  
}
