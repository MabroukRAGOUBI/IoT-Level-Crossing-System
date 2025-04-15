#include <SoftwareSerial.h> 
#include <Servo.h>
#define ServoPort 10 
#define ServoPort1 9
Servo myservo;
Servo myservo1;
int buzzer=11;
const int cap1 = 8;
const int cap2= 7;
const int red1= 6;
const int red2= 5;
const int green1= 4;
const int green2= 3;
String etat="on";
void setup() {
  Serial.begin(115200);
  myservo.attach(ServoPort);
  myservo1.attach(ServoPort1);
  pinMode(cap1,INPUT);
  pinMode(cap2,INPUT);
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  myservo.write(100);
  myservo1.write(100);
 digitalWrite(green1,HIGH);
  digitalWrite(green2,HIGH);}
 void FLB()
 { digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  int pos;
  for(pos=100;pos>=0;pos-=5){
  digitalWrite(red1,HIGH);
  digitalWrite(red2,HIGH);
  myservo.write(pos);
  myservo1.write(pos);
  tone(buzzer,650);
  delay(100);}
  noTone(buzzer);
  delay(2000);
  etat="off";}
void OLB(){
  int pos;
  for(pos=0;pos<=100;pos+=5){
  myservo.write(pos);
  myservo1.write(pos);
  delay(100);}
  etat="on";
  digitalWrite(red1,LOW);
  digitalWrite(red2,LOW);
  digitalWrite(green1,HIGH);
  digitalWrite(green2,HIGH);}
void loop() {

if(etat=="on" and(digitalRead(cap1)==0 or digitalRead(cap2)==0))
{FLB();}
if(etat=="off" and(digitalRead(cap1)==0 or digitalRead(cap2)==0))
{OLB();}
if(Serial.available())
     {
     int data;
      data = Serial.read();
      if(data==48){
         FLB();}
      if(data==49) 
         OLB();}   
      }
