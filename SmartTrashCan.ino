#include <TridentTD_LineNotify.h>
#include <WiFi.h>
#include <Wire.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;

#define SSID ""                                                      // Replace with your WiFi SSID
#define PASSWORD ""                                         // Replace with your WiFi password
#define LINE_TOKEN "TvS2nkdoPMAMBo1UhsnHscQ5Kx19woyyoMU13OP9sG2"      // Replace with your Line Notify token
#define buzzer 14

// เปิดปิด
const int trig1 = 32;
const int echo1 = 33;

//ขยะเต็ม1
const int trig2 = 18;
const int echo2 = 5;

//ขยะเต็ม2
const int trig3 = 17;
const int echo3 = 4;

int proxi = 16;

long  data;
int  distance, distanceFull, Ultra1, Ultra2, Ultra3;


void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Set Line Notify token
  LINE.setToken(LINE_TOKEN);

  // Send a test message
  LINE.notify("Hello from ESP32 on Wokwi!");

  pinMode(proxi, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  servo1.attach(12);
  servo2.attach(13);
  
}

void loop() {
SonarSensor(trig1, echo1);
Ultra1 = distance;
if (distance <= 10) {
  servo1.write(90);
  Serial.println("เปิดแล้ว");
}
if (distance > 10) {
  servo1.write(0);
  Serial.println("ปิดแล้ว");
}

SonarSensor(trig2, echo2);
Ultra2 = distanceFull;
if (distanceFull <= 10) {
   LineNotify();
   tone(buzzer, 300, 1000);  
   delay (1000);
}

SonarSensor(trig3, echo3);
Ultra3 = distanceFull;
if (distanceFull <= 10) {
   LineNotify();
   tone(buzzer, 300, 1000);  
   delay (1000);
}
int val = digitalRead(proxi);
if (val == 0) {
  servo2.write(180);
  delay (500);
}
else {
  servo2.write(-180);
  delay (500);
}

}

void SonarSensor(int trig, int echo) {
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
data = pulseIn(echo,HIGH);
distance = data*0.035/2;
distanceFull = data*0.035/2;
delay(500);
}

void LineNotify() {
  LINE.notify("ขยะเต็มแล้ว!!");
}
