#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64
#include<SoftwareSerial.h>
SoftwareSerial iot(2, 3);
SoftwareSerial serial(8, 9);
#define temp  A1
#define sw  7
#define mems A2
int a = 0, t, s, me;
int lasta = 0;
int lastb = 0;
int LastTime = 0;
int ThisTime;
bool BPMTiming = false;
bool BeatComplete = false;
int BPM = 0;
#define UpperThreshold 560
#define LowerThreshold 530

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(2);
  Serial.begin(9600);
  iot.begin(9600);
  serial.begin(9600);
  pinMode(sw, INPUT);
  pinMode(temp, INPUT);
  pinMode(mems, INPUT);
}

void loop()
{
  t = analogRead(temp);
  t = t / 4;
  s = digitalRead(sw);
  me = analogRead(mems);
  if (a > 127)
  {
    oled.clearDisplay();
    a = 0;
    lasta = a;
  }

  ThisTime = millis();
  int value = analogRead(0);
  oled.setTextColor(WHITE);
  int b = 60 - (value / 16);
  oled.writeLine(lasta, lastb, a, b, WHITE);
  lastb = b;
  lasta = a;

  if (value > UpperThreshold)
  {
    if (BeatComplete)
    {
      BPM = ThisTime - LastTime;
      BPM = int(60 / (float(BPM) / 1000));
      BPMTiming = false;
      BeatComplete = false;
      tone(8, 1000, 250);
    }
    if (BPMTiming == false)
    {
      LastTime = millis();
      BPMTiming = true;
    }
  }
  if ((value < LowerThreshold) & (BPMTiming))
    BeatComplete = true;

  oled.writeFillRect(0, 50, 128, 16, BLACK);
  oled.setCursor(10, 40);
  oled.setTextSize(1);
  oled.print("HB");
  oled.setCursor(10, 50);
  oled.setTextSize(1);
  oled.print(BPM);
  //oled.display();
  //oled.setTextSize(2);
  //oled.setCursor(30,50);
  //oled.print("05:48:45");
  oled.setCursor(40, 40);
  oled.setTextSize(1);
  oled.print("FAULT");
  oled.setCursor(40, 50);
  oled.setTextSize(1);
  oled.print(me);

  oled.setCursor(80, 40);
  oled.setTextSize(1);
  oled.print("TEMP");
  oled.setCursor(80, 50);
  oled.setTextSize(1);
  oled.print(t);
  oled.display();
  a++;
  Serial.print("T");
  Serial.print(t);
  Serial.print("S");
  Serial.print(s);
  Serial.print("M");
  Serial.print(me);
  Serial.print("H");
  Serial.println(BPM);
  serial.print("T");
  serial.print(t);
  serial.print("S");
  serial.print(s);
  serial.print("M");
  serial.print(me);
  serial.print("H");
  serial.print(BPM);
  serial.println("Z");
 delay(100);
  temp1();
  sw1();
  mems1();
  heart();
}
void heart()
{
  if (BPM > 72)
  {
    iot.println("AT+CMGF=1");
    delay(500);
    iot.println("AT+CMGS=\"+916382273986\"\r");
    delay(500);
    iot.println("Heart Beat abnormal");
    delay(500);
    iot.println((char)26);
    delay(500);
    BPM = 0;
  }
}
void temp1()
{
  if (t > 90)
  {
    
    iot.println("AT+CMGF=1");
    delay(500);
    iot.println("AT+CMGS=\"+916382273986\"\r");
    delay(500);
    iot.println("Temperature level is abnormal");
    delay(500);
    iot.println((char)26);
    delay(500);
  }
}
void sw1()
{
  if (s == 1)
  {
    iot.println("AT+CMGF=1");
    delay(500);
    iot.println("AT+CMGS=\"+916382273986\"\r");
    delay(500);
    iot.println("Help me.! Location---> Lat:13.050277 Lon:80.234044");
    delay(500);
    iot.println((char)26);
    delay(500);
    Serial.print("lavs");
  }
}
void mems1()
{
  if (me < 280)
  {
    
    iot.println("AT+CMGF=1");
    delay(500);
    iot.println("AT+CMGS=\"+916382273986\"\r");
    delay(500);
    iot.println("fall down..");
    delay(500);
    iot.println((char)26);
    delay(500);
  }
}
