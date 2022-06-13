#include <DS3231.h>

const int Relay = 4;
int ledBlue = 7;

DS3231  rtc(SDA, SCL);
Time t;

 int OnHour = 23;
 int OnMin =40;
 int OnSec = 0;
 int OffHour = 23;
 int OffMin = 40;
 int OffSec = 20;
 int buttonPin = A0; 
 int SecMin = 0 ;
 int SecMax = 20;
void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s), ");
  Serial.print(t.sec);
  Serial.print(" sec(s), ");
  Serial.println(" ");
  delay (1000);
  int auxSec = Buttons();
  
  if(t.hour == OnHour && t.min == OnMin && t.sec == OnSec){
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    }
    
    if(t.hour == OffHour && t.min == OffMin && t.sec == auxSec){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
    }
}

int Buttons(){
  int temp = analogRead(buttonPin);
  if (temp < 100)                     //Lower limit for first button - if below this limit then no button is pushed and LEDs are turned off
  {
    digitalWrite(ledBlue, LOW);
  }
  /*else if (temp < 150)                //First button limit - if below this limit but above previous limit then the first button is pressed
  {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, HIGH);
    Serial.print("um");
  }
  else if (temp < 250)                //Second button limit
  {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
    Serial.print("dois");
  }
  else if (temp < 350)                //Third button limit
  {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, HIGH);
    Serial.print("tres");  
  }*/
  else if(temp < 850)                //Fourth button limit
  {
    Serial.print("mais 1s\n");
    SecMax +=1;
  }
  else                                //If none of the previous buttons are pressed, then the fifth button must be pressed
  {
    Serial.print("menos 1 s\n");
    SecMax -=1;
  } 
  delay(100);                         //Delay for stability
  return SecMax ;
}
 
  
