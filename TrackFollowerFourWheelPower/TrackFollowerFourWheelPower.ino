#include <AFMotor.h>


AF_DCMotor motor1(1); // Front Right Motor
AF_DCMotor motor2(2); // Front Left Motor
AF_DCMotor motor3(3); // Back Left Motor
AF_DCMotor motor4(4); // Back Right Motor

int black = 0;
int white = 1;
int left_sensor;
int right_sensor;

void setup() {
  
              Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
    
              set_speed(); 
              Stop();
                delay(3000);
 
}



void loop() {
 
       set_value();
      
      
           if(left_sensor == white && right_sensor  == white )
           {
             Forward();
           } 
           
           else if(left_sensor == black && right_sensor  == black )
           {
             Stop();
             delay(100);
             Backward();
             delay(150);
             Stop();
           }
           
           else if(left_sensor == black)
           {
             Stop();
             delay(100);
             push_right();
           }
           
           else if(right_sensor == black)
           {
             Stop();
             delay(100);
             push_left();
           }
  
  
  
   
}


void set_value(){
  
                 left_sensor = digitalRead(13);
                 right_sensor = digitalRead(2);
  
}








void push_speed(){
                motor1.setSpeed(180); 
                motor2.setSpeed(180); 
                motor3.setSpeed(180); 
                motor4.setSpeed(180); 
}



void set_speed(){
        
                motor1.setSpeed(130); 
                motor2.setSpeed(130); 
                motor3.setSpeed(130); 
                motor4.setSpeed(130); 
}



void Forward(){
  
                motor1.run(BACKWARD);
                motor2.run(BACKWARD);  
                motor3.run(BACKWARD);
                motor4.run(BACKWARD);
               
}



void Backward(){
  
                motor1.run(FORWARD);
                motor2.run(FORWARD);
                motor3.run(FORWARD);
                motor4.run(FORWARD);
}





void Stop(){
  
             motor1.run(RELEASE);
             motor2.run(RELEASE);
             motor3.run(RELEASE);
             motor4.run(RELEASE);
}




void move_right(){
       
                   motor2.run(BACKWARD);
                   motor3.run(BACKWARD);
                   motor1.run(FORWARD);
                   motor4.run(FORWARD);
                   
                   delay(600);
}


void move_left(){
       
                  motor1.run(BACKWARD);
                  motor4.run(BACKWARD);
                  motor2.run(FORWARD);
                  motor3.run(FORWARD);
                  
                  delay(600);
}


void push_right(){
                   push_speed();
                   motor2.run(BACKWARD);
                   motor3.run(BACKWARD);
                   motor1.run(FORWARD);
                   motor4.run(FORWARD);
                   
                   delay(150);   
                   set_speed();             

}


void push_left(){
       
                  push_speed();
                  motor1.run(BACKWARD);
                  motor4.run(BACKWARD);
                  motor2.run(FORWARD);
                  motor3.run(FORWARD);
                  
                   
                  delay(150);   
                  set_speed();             

}
