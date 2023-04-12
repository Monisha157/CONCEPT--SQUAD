int a;
#define relay 2
const int buzzer = 7; 
#include<SoftwareSerial.h>
SoftwareSerial iot(3, 4); //Node
void setup()
{
    Serial.begin(9600);
    pinMode(relay, OUTPUT);
    pinMode(buzzer, OUTPUT); 
    digitalWrite(relay, HIGH);
    iot.begin(9600);
}
void loop()
{
  Serial.println("Reading");
  digitalWrite(relay, LOW);
  if(Serial.available()>=0)
  {
  a = Serial.read();
  Serial.println(a);
  if (a==1)
  { 
    Serial.println("Unlocking");
    digitalWrite(relay, 1);
    digitalWrite(buzzer, HIGH);  
    delay(500);        
    digitalWrite(buzzer, LOW); 
    delay(5000);  
    digitalWrite(relay,0);
  }
  else if (a==0)
  {
    Serial.println("locking");
      digitalWrite(relay, 0);
      digitalWrite(buzzer, HIGH);
      delay(2000);        
      digitalWrite(buzzer, LOW);
      Serial.print("Locking");
  }
  }
}
