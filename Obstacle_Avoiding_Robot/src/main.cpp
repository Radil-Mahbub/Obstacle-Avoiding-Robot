#include <Arduino.h>
#include <AFMotor.h>  //neccesary libraries
#include <NewPing.h>
#include <Servo.h> 

#define trigPin A0
#define echoPin A1
const int MAX_DISTANCE = 100;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
float duration, distance;

Servo myservo; //initialises the servo motor

#define MAX_SPEED 150 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
  
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
 
void setup() 
{
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
 
void loop() 
{
  
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=25) //steering system
 {
  moveStop();
  delay(100);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
 
  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  } 
 
  else
 
  {
    turnLeft();
    moveStop();
  }
 } 
 
 else
 {
  moveForward();
 }
 
 distance = readPing();
 
}


int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}
 
int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}
 
int readPing()
{ 
  delay(100);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
 
void moveStop() 
{
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 
 
void moveForward() 
{
 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly brings the speed up 
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}
 
void turnRight() 
{
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(3500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft()
{ 
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(3500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
