
#include <AFMotor.h>

AF_DCMotor motor1(1);     //dc motor initialization 
AF_DCMotor motor2(2);




//UNO TO  MOTOR SHIELD CONNECTION

int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC
int enable1Pin = 6; // pin 1 on L293D IC
int motor2Pin1 = 8; // pin 10 on L293D IC
int motor2Pin2 = 9; // pin 15 on L293D IC
int enable2Pin = 11; // pin 9 on L293D IC



void setup()
{
Serial.begin(9600);//baudrate


pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(enable1Pin, OUTPUT);
pinMode(motor2Pin1, OUTPUT);
pinMode(motor2Pin2, OUTPUT);
pinMode(enable2Pin, OUTPUT);
    // sets enable1Pin and enable2Pin high so that motor can turn on:
digitalWrite(enable1Pin, HIGH);
digitalWrite(enable2Pin, HIGH);

SetSpeed(); 
              Stop();
                delay(3000);
               // move_left();
               // move_right();

              Forward();
}

void loop()
{

int i ;
  if(digitalRead(A0)==1  &&digitalRead(A1)==1 )
  {
    Forward();
  }
  else if (digitalRead(A0)==1  &&digitalRead(A1)==0  ) 
  {
     for ( i = 0 ; i < 250 ; i++ )  Stop();
move_right();
   // move_left();
  }
   else if (digitalRead(A0)==0  &&digitalRead(A1)==1 ) 
  {
     for ( i = 0 ; i < 250 ; i++ )  Stop();
move_left();
    //move_right();
  }
  else
  {
    Forward();
  }
  }

void SetSpeed(){

                motor1.setSpeed(70); 
                motor2.setSpeed(70); 

}



void Forward()
{

               motor1.run(FORWARD);
               motor2.run(FORWARD);

}


void move_left(){
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(200);
}

void move_right(){
motor2.run(BACKWARD);
motor1.run(FORWARD);
delay(200);
}

void Stop(){

             motor1.run(RELEASE);
             motor2.run(RELEASE);

}









void _FORWARD()
{

digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
}

void LEFT()
{
digitalWrite(motor1Pin1, HIGH); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, LOW);
}

void RIGHT()
{

digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
}

void REVERSE()
{

digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
}

void STOP()
{

digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, LOW);
}
