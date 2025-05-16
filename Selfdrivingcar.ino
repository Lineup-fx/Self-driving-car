#include <Servo.h>
int Echo1=10; //output pin from left sensor, that transmits data to arduino
int trig1=11; //input pin into ultrasonic left sensor that sends an output pulse when enabled
int Echo2=12; //output pin from right sensor
int trig2=13; //input pin into right sensor to send a wave
Servo myservo;
void setup() {
  Serial.begin(9600);
  myservo.attach(9); //servo motor attached to pin 9
  pinMode(Echo1, INPUT); 
  pinMode(trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(trig2, OUTPUT);
}

void loop() {
  float cent1; //stores distance from left sensor 
  float cent2; //stores distance from right sensor
  int pulse1; //stores the time that pulse takes to travel back and forth from obstacle to left sensor
  int pulse2; //stores pulse time for right sensor
  digitalWrite(trig1, LOW);
  delay(10);
  digitalWrite(trig1, HIGH);
  delay(10);
  digitalWrite(trig1, LOW);
  pulse1=pulseIn(Echo1, HIGH);
  cent1=pulse1/29.387/2;
  //cent1=50;
  digitalWrite(trig2, LOW);
  delay(10);
  digitalWrite(trig2, HIGH);
  delay(10);
  digitalWrite(trig2, LOW);
  pulse2=pulseIn(Echo2, HIGH);
  cent2=pulse2/29.387/2;
  //cent2=50;
  Serial.print("first value "+ (String)cent1 +" , ");
  Serial.println("Second value  "+ (String)cent2);
  int id;
  float cent;
  if(cent1<cent2){
    id=1;//to id the sensor which is closer to obstacle
    cent=cent1;//stores minimum distance value
  }
  else{
    id=2;//to id the sensor which is closer to obstacle
    cent=cent2;//stores minimum distance value
  }
  if(cent<17){
    if(id==1){//right subroutine: the obstacle is closer to left sensor
      myservo.write(45);
      Serial.println("turning right");
      delay(1100);
      myservo.write(90);
      delay(500);
    }
    else{//left subroutine: the obstacle is closer to right sensor
      myservo.write(135);
      Serial.println("turning left");
      delay(1100);
      myservo.write(90);
      delay(500);
    }
  }
  delay(100);
}