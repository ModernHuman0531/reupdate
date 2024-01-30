// state = 0: auto
// state = 1: manual

#include <string.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define LEFT_MOTOR1 9
#define LEFT_MOTOR2 8
#define LEFT_PWM 3
#define RIGHT_MOTOR1 10
#define RIGHT_MOTOR2 12
#define RIGHT_PWM 11
#define IR_LEFT 5
#define IR_MID 6
#define IR_RIGHT 7

class Motor
{
public:
    Motor(int in1, int in2, int pwm) :
        _in1(in1), _in2(in2), _pwm(pwm)
    {
        pinMode(_in1, OUTPUT);
        pinMode(_in2, OUTPUT);
        pinMode(_pwm, OUTPUT);
    }

    void forward(int speed)
    {
        digitalWrite(_in1, HIGH);
        digitalWrite(_in2, LOW);
        analogWrite(_pwm, speed);
    }

    void backward(int speed)
    {
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, HIGH);
        analogWrite(_pwm, speed);
    }

private:
    int _in1;
    int _in2;
    int _pwm;
};

class Chassis
{
public:
    Chassis(Motor& left, Motor& right) :
        _left(left), _right(right)
    {}

    void forward(int speed)
    {
        _left.forward(speed);
        _right.forward(speed);
    }

    void backward(int speed)
    {
        _left.backward(speed);
        _right.backward(speed);
    }

    void turnLeft(int speed)
    {
        _left.backward(speed);
        _right.forward(speed);
    }

    void turnRight(int speed)
    {
        _left.forward(speed);
        _right.backward(speed);
    }

    void stop()
    {
        _left.forward(0);
        _right.forward(0);
    }
private:
    Motor& _left;
    Motor& _right;
};

class IRSensor
{
public:
    IRSensor(int pin) : _pin(pin)
    {
        pinMode(_pin, INPUT);
    }

    bool read()
    {
        return digitalRead(_pin);
    }

private:
    int _pin;
};

class IRArray
{
public:
    IRArray(IRSensor& left, IRSensor& mid, IRSensor& right) :
        _left(left), _mid(mid), _right(right)
    {}

    int read()
    {
        bool leftValue = _left.read();
        bool midValue = _mid.read();
        bool rightValue = _right.read();

        return (leftValue << 2) | (midValue << 1) | rightValue; 
    }

private:
    IRSensor& _left;
    IRSensor& _mid;
    IRSensor& _right;
};

int state = 0;
int time1 = 300;
int time2 = 100;
SoftwareSerial BT(4, 13);
Chassis chassis(
    Motor(LEFT_MOTOR1, LEFT_MOTOR2, LEFT_PWM),
    Motor(RIGHT_MOTOR1, RIGHT_MOTOR2, RIGHT_PWM)
);
IRArray irArray(
    IRSensor(IR_LEFT),
    IRSensor(IR_MID),
    IRSensor(IR_RIGHT)
);

void setup()
{
    Serial.begin(9600);
    BT.begin(9600);
}

void loop()
{
    if(state == 0)
    {
        // auto code
        sensorstatus = irArray.read();
        switch(sensorstatus)
        {
        case 0b000:
            chassis.stop();
            break;

        case 0b001:
            chassis.stop();
            break;

        case 0b010:
            chassis.stop();
            break;

        case 0b011:
            chassis.turnLeft(255);
            break;

        case 0b100:
            chassis.stop();
            break;

        case 0b101:
            chassis.forward(255);
            break;

        case 0b110:
            chassis.turnRight(255);
            break;

        case 0b111:
            chassis.backward(255);
            break;
        }
    }

    if (state == 1)
    {
        // manual code
        if (BT.available())
        {
            char c = BT.read();
            switch (c)
            {
            case 'F':
                chassis.forward(255);
                break;

            case 'B':
                chassis.backward(255);
                break;

            case 'L':
                chassis.turnLeft(255);
                break;

            case 'R':
                chassis.turnRight(255);
                break;

            case 'S':
            case '0':
                chassis.stop();
                break;;
            }
        }
    }
}