/*

  Smart Dustbin Implementation using Raspberry Pi Pico, Servo Motor, Camera Module and Ultrasonic Sensor.
   
 */

#include <Servo.h>   //servo library

Servo servo;    
int trigPin = 12;    // Trigger pin
int echoPin = 13;    // Echo Pin
int servoPin = 10;   // Servo Motor Pin
int camPin = 9;      // Camera Pin

long duration, dist, average;  
long aver[3];        //array for average


void setup() {    
   
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    pinMode(camPin, INPUT);
    servo.write(150);                   //close cap on power on
    delay(100);
    servo.detach();
}

void measure() {
   
    digitalWrite(10,HIGH);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    dist = (duration/2) / 29.1;         //obtain distance
   
}
void loop() {
   
    for (int i=0;i<=2;i++) {            //average distance
        measure();              
        aver[i]=dist;            
        delay(10);                      //delay between measurements
     }
    dist=(aver[0]+aver[1]+aver[2])/3;    
    int a= digitalRead(camPin);
    if ( dist<30 && a == 1)  {
 
                                        //Change distance as per your need
       servo.attach(servoPin);
       delay(1);
       servo.write(180);  
       delay(5000);      
       servo.write(0);    
       delay(1000);
       servo.detach();      
    }
 
    Serial.print(dist);
}
