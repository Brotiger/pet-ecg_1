int analogPin = 0;
int buttonPin = 4;
boolean lastButton = HIGH;
boolean currentButton = HIGH;
boolean ecgOn = false;
int ledPin = 13;
int lo_0 = 10;
int lo_1 = 11;
int ledPin_g = 3;
int ledPin_r = 12;
void setup()
{
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(lo_0, INPUT); // Настройка выхода L0-
  pinMode(lo_1, INPUT); // Настройка выхода L0+
  pinMode(ledPin_g, OUTPUT);
  pinMode(ledPin_r, OUTPUT);
  digitalWrite(ledPin_g, HIGH);
}

boolean debounce(boolean last){
  boolean current =  digitalRead(buttonPin);
  if(last != current){
    delay(5);
    current =  digitalRead(buttonPin);
  }
  return current;
}
void loop()
{

  currentButton = debounce(lastButton);
  if (lastButton == HIGH && currentButton == LOW){
    ecgOn = !ecgOn;
  }
  lastButton = currentButton;
  
  digitalWrite(ledPin, ecgOn);
  if(ecgOn){
    if((digitalRead(lo_0) == 1)||(digitalRead(lo_1) == 1))
    {
      digitalWrite(ledPin_r, HIGH);
      Serial.println("error");
    }
    else{
      digitalWrite(ledPin_r, LOW);
      Serial.println(analogRead(analogPin));
    }
    delay(5);
  }else{
    digitalWrite(ledPin_r, LOW);
  }
}
