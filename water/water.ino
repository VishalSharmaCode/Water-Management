#include <IOXhop_FirebaseESP32.h>
#include<WiFi.h>
char ssid[] = "";
char password[] = "";
char firebaseHost[] = "";
char firebaseKey[] = "";


int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input1 = 13;
const int input2 = 12;
const int input3 = 14;
const int input4 = 27;
const int input5 = 26;
const int input6 = 25;
const int input7 = 33;
void setup()
{
Serial.begin(9600);
delay(2000);
pinMode(input1,INPUT);
pinMode(input2,INPUT);
Serial.begin(9600);
      WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("*");
    delay(500);
  }
   Serial.println("WiFi Connected");
  Firebase.begin(firebaseHost, firebaseKey);
  Serial.println("Firebase Connected");
}
void loop()
{
X = pulseIn(input1, HIGH);
Y = pulseIn(input1, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("TOTAL:");
Serial.print( TOTAL);
Serial.println(" L");
Firebase.setFloat("Flow1",0);
}
else
{
TOTAL = TOTAL + LS;
Serial.println(FREQUENCY);

Serial.print("VOL.: ");
Serial.print(WATER);
Serial.println(" L/M");
Firebase.setFloat("Flow1",WATER);

Serial.print("TOTAL:");
Serial.print( TOTAL);
Serial.println("L");
Firebase.setFloat("Total1",TOTAL);
}
}
//delay(1000);
}
