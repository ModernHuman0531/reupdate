// state = 0: auto
// state = 1: manual
#include<string.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#define Left_motor1 9
#define Left_motor2 8
#define Left_pwm 3
#define Right_motor1 10
#define Right_motor2 12
#define Right_pwm 11
#define IR_left 5
#define IR_mid 6
#define IR_right 7
int state = 0;
int Time1=300,Time2=100;
char moterstatus,sensorstatus;
SoftwareSerial BT(4,13);
class motor
{
  public:
    motor(int Left_motor1,int Left_motor2,int Left_pwm,int Right_motor1,int Right_motor2,int Right_pwm);
    void move(int dir);
  private:
    int _Left_motor1,_Left_motor2,_Left_pwm,_Right_motor1,_Right_motor2,_Right_pwm;
}
class Sensor
{
  public:
    Sensor(int IR_left,int IR_mid,int IR_right);
    int sensor_value();
  private:
    int _IR_left,_IR_mid,_IR_right;
}
motor::motor(int Left_motor1,int Left_motor2,int Left_pwm,int Right_motor1,int Right_motor2,int Right_pwm)
{
  pinMode(Left_motor1,OUTPUT);
  pinMode(Left_motor2,OUTPUT);
  pinMode(Right_motor1,OUTPUT);
  pinMode(Right_motor2,OUTPUT);
  pinMode(Left_pwm,OUTPUT);
  pinMode(Right_pwm,OUTPUT);
  _Left_motor1=Left_motor1;
  _Left_motor2=Left_motor2;
  _Left_pwm=Left_pwm
  _Right_motor1=Right_motor1
  _Right_motor2=Right_motor2;
  _Right_pwm=Right_pwm;
}
void motor::move(int dir);
{
   if(dir==1)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time2);
  }
  else if(dir==0)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time1);
  }
  else if(dir==2)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time2);
  }
  else if(dir==3)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,0);
    analogWrite(Right_pwm,200);
    delay(Time2);
  }
  else if(dir==4)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,200);
    analogWrite(Right_pwm,0);
    delay(Time2);
  }
  else if(dir==5)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,85);
    analogWrite(Right_pwm,0);
    delay(Time2);
  }
  else if(dir==6)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,0);
    analogWrite(Right_pwm,85);
    delay(Time2);
  }
}
Sensor::Sensor(int IR_left,int IR_mid,int IR_right)
{
  pinMode(IR_left,INPUT);
  pinMode(IR_mid,INPUT);
  pinMode(IR_right,INPUT);
  _IR_left=IR_left;
  _IR_mid=IR_mid;
  _IR_right=IR_right;
}
int Sensor::sensor_value()
{
  if(digitalRead(IR_mid)==LOW&&digitalRead(IR_right)==HIGH&&digitalRead(IR_left)==LOW)
  {
    Serial.println("Forward");
    return 1;
  }
  else if(IR_left_value==HIGH&&IR_right_value==HIGH&&IR_mid_value==HIGH)
  {
    Serial.println("TurnLeft_quickly");
    return 2;
  }
  else if(IR_right_value==LOW&&IR_mid_value==HIGH&&IR_left_value==LOW)
  {
    Serial.println("TurnRight_quickly");
    return 3;
  }
  else if(IR_mid_value==HIGH&&IR_right_value==HIGH&&IR_left_value==LOW)
  {
    Serial.println("Backward");
    return 4;
  }
  else if(IR_right_value==LOW&&IR_mid_value==LOW&&IR_left_value==HIGH)
  {
    Serial.println("Stop");
    return 5;
  }
  else if(IR_right_value==LOW&&IR_mid_value==LOW&&IR_left_value==LOW)
  {
    Serial.println("TurnRight_slowly");
    return 6;
  }
  else if(IR_left_value==HIGH&&IR_right_value==HIGH&&IR_mid_value==LOW)
  {
    Serial.println("TurnLeft_slowly");
    return 7;
  }
  else 
  {
    Serial.println("else");
    return 8;
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin(9600); // 設定和 HC-06 通訊的速度 (預設 9600) 
}
void loop() {
  if(state == 0) // auto
  {
    // auto code here
    sensorstatus=sensor.sensor_value();
    switch(sensor_value)
    {
      case 1:
        motor.move(2);
        motor.move(0);
        break;
      case 2:
        motor.move(3);
        motor.move(0);
        break;
      case 3:
        motor.move(4);
        motor.move(0);
        break;
      case 4:
        motor.move(6);
        motor.move(0);
        motor.move(5);
        motor.move(0);
        break;
      move 5:
        motor.move(0);
        state = 1;
        break;
      move 6:
        motor.move(5);
        motor.move(0);
        break;
      move 7:
        motor.move(6);
        motor.move(0);
        break;
      move 8:
        motor.move(0);
        break;
    }
  }
  else if(state == 1) // manual
  {
      // manual code here
    if (BT.available())
    {
      moterstatus=BT.read();
      Serial.println(moterstatus); 
    }
    switch (moterstatus)
    { 
      case 'F':
        Serial.println("Forward");
        motor.move(2);
        break;
      case 'B':
        Serial.println("Backward");
        motor.move(1);
        break;
      case 'L':
        Serial.println("TurnLeft");
        motor.move(4);
        break;
      case 'R':
        Serial.println("TurnRight");
        motor.move(3);
        break;
      case 'S':
        Serial.println("Stop");
        motor.move(0);
        break;
      case '0':
        Serial.println("Stop");
        motor.move(0);
        break;
    }
  }
}