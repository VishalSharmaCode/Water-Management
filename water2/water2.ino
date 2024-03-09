#include <IOXhop_FirebaseESP32.h>
#include<WiFi.h>
char ssid[] = "";
char password[] = "";
char firebaseHost[] = "";
char firebaseKey[] = "";


int X;
int Y;
int X2;
int Y2;
int X3;
int Y3;
int X4;
int Y4;
int X5;
int Y5;
int X6;
int Y6;
int X7;
int Y7;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float TOTAL2=0;
float TOTAL3=0;
float WATER2=0;
float WATER3;
float LS = 0;
const int input1 = 13;
const int input2 = 12;
const int input3 = 14;        
const int input4 = 27;
const int input5 = 26;
const int input6 = 25;
const int input7 = 33;
const int relay=15;
void setup()
{
Serial.begin(9600);
delay(2000);
pinMode(12,INPUT);
pinMode(14,INPUT);
pinMode(27,INPUT);
pinMode(15,OUTPUT);
pinMode(2,OUTPUT);
digitalWrite(15,HIGH);
Serial.begin(9600);
      WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("*");
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
  }
   Serial.println("WiFi Connected");
  Firebase.begin(firebaseHost , firebaseKey);
  Serial.println("Firebase Connected");
}
void loop()
{
Sensor1();
Sensor2();
Sensor3();
checkMotor();
}
void checkMotor()
{
  bool motor;
  motor=Firebase.getBool("MotorControle");
  //Serial.println(motor);
  if(motor == true)
  {
    Serial.println("motor is true");
    digitalWrite(15,LOW);
  }
  else
  {
    Serial.println("motor is off");
    digitalWrite(15,HIGH); 
  }
}
void Sensor1(){
  X = pulseIn(14, HIGH);
Y = pulseIn(14, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("TOTAL 1:");
Serial.print( TOTAL);
Serial.println(" L");
Firebase.setFloat("leftTap Flow Speed",0);
}
else
{
TOTAL = TOTAL + LS;
Serial.println(FREQUENCY);

Serial.print("VOL.1: ");
Serial.print(WATER);
Serial.println(" L/M");
Firebase.setFloat("leftTap Flow Speed",WATER);

Serial.print("TOTAL 1:");
Serial.print( TOTAL);
Serial.println("L");
Firebase.setFloat("Volume of Flow leftTap ",TOTAL);
}
}
//delay(1000);
}
void Sensor2(){
  X2 = pulseIn(input2, HIGH);
Y2 = pulseIn(input2, LOW);
TIME = X2 + Y2;
FREQUENCY = 1000000/TIME;
WATER2 = FREQUENCY/7.5;
LS = WATER2/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("TOTAL 2=:");
Serial.print( TOTAL2);
Serial.println(" L");
Firebase.setFloat("Left Tank OUTPUT Flow2",0);
}
else
{   
TOTAL2 = TOTAL2 + LS;
//Serial.println(FREQUENCY);

Serial.print("VOL.2=: ");
Serial.print(WATER2);
Serial.println(" L/M");
Firebase.setFloat("Left Tank OUTPUT Flow",WATER2);

Serial.print("TOTAL 2=:");
Serial.print( TOTAL2);
Serial.println("L");
Firebase.setFloat("Volume Left Tank OUTPUT ",TOTAL2);
}
}
//delay(1000);
}

void Sensor3(){
  X3 = pulseIn(27, HIGH);
Y3 = pulseIn(27, LOW);
TIME = X3 + Y3;
FREQUENCY = 1000000/TIME;
WATER2 = FREQUENCY/7.5;
LS = WATER2/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("TOTAL Motor=:");
Serial.print( TOTAL3);
Serial.println(" L");
Firebase.setFloat("Motor OUTPUT Flow",0);
}
else
{   
TOTAL3 = TOTAL3 + LS;
//Serial.println(FREQUENCY);

Serial.print("VOL. Motor=: ");
Serial.print(WATER3);
Serial.println(" L/M");
Firebase.setFloat("Motor OUTPUT Flow",WATER3);

Serial.print("TOTAL Motor=:");
Serial.print( TOTAL3);
Serial.println("L");
Firebase.setFloat("Volume Motor OUTPUT",TOTAL3);
}
}
//delay(1000);
}
