#include <AFMotor.h>
#include<NewPing.h>

#define TRIGGER_PIN_Front  A0  // Front Sonar Sensor
#define ECHO_PIN_Front     A1  

#define TRIGGER_PIN_Right  A2  // Right Sonar Sensor
#define ECHO_PIN_Right     A3  

#define TRIGGER_PIN_Left   A4  // Left Sonar Sensor
#define ECHO_PIN_Left      A5  

#define TRIGGER_PIN_Back   2   // Back Sonar Sensor
#define ECHO_PIN_Back      13  


#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


// NewPing setup of pins and maximum distance.
NewPing sonarFront(TRIGGER_PIN_Front, ECHO_PIN_Front, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_PIN_Right, ECHO_PIN_Right, MAX_DISTANCE);
NewPing sonarLeft(TRIGGER_PIN_Left, ECHO_PIN_Left, MAX_DISTANCE);
NewPing sonarBack(TRIGGER_PIN_Back, ECHO_PIN_Back, MAX_DISTANCE);


AF_DCMotor motor1(1); // Front Right Motor
AF_DCMotor motor2(2); // Front Left Motor
AF_DCMotor motor3(3); // Back Left Motor
AF_DCMotor motor4(4); // Back Right Motor


unsigned int uS_front;
unsigned int uS_right;
unsigned int uS_left;
unsigned int uS_back;

unsigned int front_distance;
unsigned int right_distance;
unsigned int left_distance;
unsigned int back_distance;

void setup() {
  
              Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
    
              set_speed(); 
              Stop();
                delay(3000);
 
}



void loop() {
  delay(100);
  set_distance();
  
  Serial.print("Front: ");
  Serial.print(front_distance);
  Serial.println("cm");
  
  Serial.print("Left: ");
  Serial.print(left_distance);
  Serial.println("cm");
  
  Serial.print("Right: ");
  Serial.print(right_distance);
  Serial.println("cm");
  
  Serial.print("Back: ");
  Serial.print(back_distance);
  Serial.println("cm");
   


     
     if( front_distance > 30 )
         {
           Forward();
           set_distance();
         }
     else
        {
          Stop();
      
          make_turn();
        }
    
     if( right_distance <= 12 && left_distance <= 12 )
         {
             Stop(); 
             move_backward();   
         }       
              
              
     if( left_distance <= 20 )
         {
                if( right_distance > 12 )
                     {
                         push_right();
                     }                       
                     
                 else
                     {
                       Stop();
                       move_backward();
                     }  
                     
                set_distance();      
          }    
  
  
     if( right_distance <= 20 )
          {
                  if( left_distance > 12 )
                       {
                         push_left();
                       }                       
                     
                 else
                     {
                       Stop();
                       move_backward();
                     }            
             
          }
   
}











void make_turn(){
   
                Stop();
                
                set_distance();
                
                if( right_distance < 20 && left_distance < 20 )
                {
                            Stop();
                            move_backward();
                  
                }
                 
                else if( right_distance >= left_distance )
                {
                           move_right();
                         
                }
                
                else if( right_distance < left_distance )
                {
                           move_left();
                         
                }
                
}




void move_backward(){
  
  while(true)
  {
       set_distance();
     
        if( back_distance > 20 )
           {
                  Backward();
                  set_distance(); 
                  
                      if( right_distance > 30 || left_distance > 30 )
                         {
                                      
                                  if( right_distance >= left_distance )
                                     {
                                          push_right();
                                          delay(100);
                                          loop();
                                     }
            
                                  else if( left_distance > right_distance  )
                                     {
                                          push_left();
                                          delay(100);
                                          loop();
                                     }
            
                              break;
                           }
            }  
  
        else
        {
          Stop();
          check_for_space();
        }
            
        
  }     
  
}






void check_for_space()
{ 
        Stop();
  
  while(true)
  {
          set_distance();
       
          if( front_distance > 30 )
          {
            loop();
            break;
          }
          
          if( right_distance > 30 || left_distance > 30 )
          {
                                      
                  if( right_distance >= left_distance )
                    {
                        push_right();
                        delay(100);
                        loop();
                    }
            
                  else if( left_distance > right_distance  )
                    {
                       push_left();
                       delay(100);
                       loop();
                    }
            
               break;
           }
          
          if(back_distance > 20 )
          {
            
            move_backward();
            break;
            
          }
   
  }  
}




/*void set_distance()
{
  
  int front_Distance_Count[3];
  int right_Distance_Count[3];
  int left_Distance_Count[3];
  int back_Distance_Count[3];
    
                  for(int j=0; j<3; j++ )
                     {                        
                           uS_front = sonarFront.ping();
                           front_Distance_Count[j] = uS_front / US_ROUNDTRIP_CM;
                               if(front_Distance_Count[j] == 0)
                                   {
                                    front_Distance_Count[j] = MAX_DISTANCE;
                                   }                                   
                                   
                                              
                           uS_right = sonarRight.ping();
                           right_Distance_Count[j] = uS_right / US_ROUNDTRIP_CM; 
                              if(right_Distance_Count[j] == 0)
                                  {
                                    right_Distance_Count[j] = MAX_DISTANCE;
                                  }
                           
                           
                           uS_left = sonarLeft.ping();
                           left_Distance_Count[j] = uS_left / US_ROUNDTRIP_CM;
                               if(left_Distance_Count[j] == 0)
                                   {
                                    left_Distance_Count[j] = MAX_DISTANCE;
                                   }
                                   
                                   
                               
                           uS_back = sonarBack.ping();
                           back_Distance_Count[j] = uS_back / US_ROUNDTRIP_CM;
                               if(back_Distance_Count[j] == 0)
                                   {
                                    back_Distance_Count[j] = MAX_DISTANCE;
                                   }     
                        
                                   
                     }
                     
                   right_distance = 0;
                   left_distance = 0;
                   front_distance = 0;
                   back_distance = 0;
                     
                 for(int j=0; j<3; j++ )
                     {
                       front_distance = front_distance + front_Distance_Count[j];
                       right_distance = right_distance + right_Distance_Count[j];
                       left_distance = left_distance + left_Distance_Count[j];
                       back_distance = back_distance + back_Distance_Count[j];
                       
                     }    
                     
                     front_distance = front_distance / 3;
                     right_distance = right_distance / 3;
                     left_distance = left_distance / 3;
                     back_distance = back_distance / 3;
                     
                     
}

*/




void set_distance(){
  
               uS_back  = sonarBack.ping();
               uS_front = sonarFront.ping();        
               uS_right = sonarRight.ping();
               uS_left  = sonarLeft.ping(); 
               
               
                           
                           
                front_distance = uS_front / US_ROUNDTRIP_CM;
                right_distance = uS_right / US_ROUNDTRIP_CM; 
                left_distance  = uS_left  / US_ROUNDTRIP_CM;
                back_distance  = uS_back  / US_ROUNDTRIP_CM;
                
                              
                         if(front_distance == 0)
                                front_distance = MAX_DISTANCE;
                                                                                                 
                         if(right_distance == 0)
                                right_distance = MAX_DISTANCE;
                                                  
                         if(left_distance == 0)
                                left_distance = MAX_DISTANCE;
                                                         
                         if(back_distance == 0)
                                back_distance = MAX_DISTANCE;
                                   
}








void push_speed(){
                motor1.setSpeed(250); 
                motor2.setSpeed(250); 
                motor3.setSpeed(250); 
                motor4.setSpeed(250); 
}



void set_speed(){
        
                motor1.setSpeed(140); 
                motor2.setSpeed(140); 
                motor3.setSpeed(140); 
                motor4.setSpeed(140); 
}



void Forward(){
  
               motor1.run(FORWARD);
               motor2.run(FORWARD);
               motor3.run(FORWARD);
               motor4.run(FORWARD);
}



void Backward(){
  
                motor1.run(BACKWARD);
                motor2.run(BACKWARD);  
                motor3.run(BACKWARD);
                motor4.run(BACKWARD);
}





void Stop(){
  
             motor1.run(RELEASE);
             motor2.run(RELEASE);
             motor3.run(RELEASE);
             motor4.run(RELEASE);
}




void move_right(){
       
                   motor2.run(FORWARD);
                   motor3.run(FORWARD);
                   motor1.run(BACKWARD);
                   motor4.run(BACKWARD);
                   
                   delay(600);
}


void move_left(){
       
                  motor1.run(FORWARD);
                  motor4.run(FORWARD);
                  motor2.run(BACKWARD);
                  motor3.run(BACKWARD);
                  
                  delay(600);
}


void push_right(){
       
                   motor2.run(FORWARD);
                   motor3.run(FORWARD);
                   motor1.run(BACKWARD);
                   motor4.run(BACKWARD);
                   
                   delay(100);                

}


void push_left(){
       
                  motor1.run(FORWARD);
                  motor4.run(FORWARD);
                  motor2.run(BACKWARD);
                  motor3.run(BACKWARD);
                   
                   delay(100);                

}
