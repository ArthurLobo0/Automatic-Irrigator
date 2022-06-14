#include <DS3231.h>

const int Relay = 4;
int ledBlue = 7;

DS3231  rtc(SDA, SCL);
Time t;

 int OnHour = 23;
 int OnMin =40;
 int OnSec = 0;
 //int OffHour = 23;
 //int OffMin = 40;
 //int OffSec = 20;
 
 int buttonPin = A0; 
 int SecMax ;
 int MinMax;
 int HoraMax;
void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  HoraMax = 23;
  MinMax = 40;
  SecMax = 20;
  
}

void loop() {
 // t = rtc.getTime();
 // Serial.print(t.hour);
 // Serial.print(" hour(s), ");
 // Serial.print(t.min);
  //Serial.print(" minute(s), ");
  //Serial.print(t.sec);
  //Serial.print(" sec(s), ");
  //Serial.println(" ");
  int auxSec = Buttons();
  delay (20);
  if(t.hour == OnHour && t.min == OnMin && t.sec == OnSec){
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    }
  if(t.hour == HoraMax && t.min == MinMax && t.sec == auxSec){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
    }
}

int Buttons(){ //This funtions reads which button is being pressed
  int temp = analogRead(buttonPin);
  //Serial.println(temp);
  if (temp < 100)                  
  {
  }
  else if(temp < 650)  //850              //Left Button is pressed
  {
    SecMax +=1;
  }
  else                                //Right Button is pressed
  {
    SecMax -=1;
  } 
  arredonda();
  delay(100);                         
  return SecMax ;
}
 
int arredonda(){ //This function make the correction of the time (>60 seconds or >60 minutes, etc)
 if(SecMax >=60 ){ 
  MinMax = MinMax + SecMax/60;
  SecMax = SecMax - 60;
  HoraMax = HoraMax + MinMax/60;
  if(MinMax >=60) {
  MinMax = MinMax -60;
  if(HoraMax >= 24){
  HoraMax = HoraMax - 24; 
     }
    }
  }
  if(SecMax < 0){
    MinMax = MinMax - 1;
    SecMax = 59;
    if(MinMax < 0){
      HoraMax = HoraMax - 1;
      MinMax = 59;
  if(HoraMax <0){
    HoraMax = 23;
      }
    }
  }
}
