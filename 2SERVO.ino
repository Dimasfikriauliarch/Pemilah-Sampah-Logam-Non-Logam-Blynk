#define BLYNK_PRINT Serial // library hc-04
#include <Servo.h>
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//sensor sampah 1
#define trigger1 D1
#define echo1 D2

//sensor sampah 2
#define trigger2 D5
#define echo2 D6

char auth[] = "_a8KXM6dw9fvn1sV5PZhZNtHxSh2YMuS";

char ssid[] = "iPhone";
char pass[] = "123123123";

Servo servo1;
Servo servo2;
int sensor=D0;
int sensor1=D7;
int nonlogam;
int logam;
int pos=0;


long duration1 , duration2; 
int distance1 , distance2;
WidgetLCD lcd1(V5);
WidgetLCD lcd2(V6);

void setup() {

servo1.attach(D4);
servo2.attach(D3);
pinMode(sensor, INPUT);
pinMode(sensor1, INPUT);


pinMode(trigger1,OUTPUT); //PIN TRIGGER SAMPAH 1
pinMode(echo1,INPUT); //Pin echo sampah 1  
pinMode(trigger2,OUTPUT); //pin trigger sampah 2
pinMode(echo2,INPUT); //pin echo sampah 2

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);

lcd1.clear();
lcd1.print(0, 0, "sampah1 jarak cm : ");
lcd2.clear();
lcd2.print(0, 0, "sampah1 jarak cm : ");
}


void loop(){

Blynk.run();
lcd1.clear();  
lcd1.print(0, 0, "Tong sampah ");
lcd1.print(0, 1, "logam cm: ");
lcd2.clear();  
lcd2.print(0, 0, "Tong sampah"); 
lcd2.print(0, 1, "nonlogam cm: ");  

nonlogam = digitalRead(sensor);
logam = digitalRead(sensor1);
delay(1000);

if (nonlogam==1&&logam==1){ // non logam
  servo2.write(180);
  Serial.print("object detected");
  delay(500);
}
else {(nonlogam==0&&logam==0);
  servo2.write(0);
  Serial.print("object detected");
  delay(500);
}
if (nonlogam==1&&logam==0){  
  servo1.write(0);
  Serial.print("object detected");
  delay(500);
}
else {(nonlogam==0&&logam==0);   // logam deteksi
  servo1.write(180);
  Serial.print("object detected logam");
  delay(500);
}


digitalWrite(trigger1, LOW);
delayMicroseconds(2);

digitalWrite(trigger1, HIGH);
delayMicroseconds(10);

digitalWrite(trigger1, LOW);
duration1 = pulseIn(echo1, HIGH);
distance1 = duration1 *0.034/2;
lcd1.print(10, 1, distance1);
Serial.print("SAMPAH NON LOGAM JARAK : ");
Serial.println(distance1);


digitalWrite(trigger2, LOW);
delayMicroseconds(2);

digitalWrite(trigger2, HIGH);
delayMicroseconds(10);

digitalWrite(trigger2, LOW);
duration2 = pulseIn(echo2, HIGH);
distance2 = duration2 *0.034/2;
lcd2.print(13, 1, distance2);
Serial.print("SAMPAH LOGAM JARAK CM : ");
Serial.println(distance2);

// menulis pada serial monitor pembacaan sensor hujan dan cahaya
// hasil output data sensor bisa dilihat di serial monitor arduino


if (distance1<=5){
lcd1.print(0,0, "SAMPAH 1 SUDAH PENUH");
Blynk.notify("BAK SAMPAH LOGAM SUDAH PENUH");
}

if (distance2<=5){
lcd2.print(0,0, "SAMPAH 2 SUDAH PENUH");
Blynk.notify("BAK SAMPAH NONLOGAM SUDAH PENUH");
  delay(300);
}

}
