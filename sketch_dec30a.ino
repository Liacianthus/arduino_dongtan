#include <Servo.h>        
#include <SoftwareSerial.h>
#include <Wire.h>

#define Slave 0x04
byte rec[128];

SoftwareSerial BTserial(10, 11);   
          
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int a = 0;   
int A=0;
int B=0;          
int C=0;
int D=0;      
int pointer[4];

void setup()
{
  Wire.begin(Slave);
  servo1.attach(9);   
  servo2.attach(12);
  servo3.attach(13);
  servo4.attach(8);
  
  BTserial.begin(9600); 
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  
  Serial.begin(9600);
}
void loop()
{
 Wire.onReceive(action);
 
 if(BTserial.available())           
    a = BTserial.read();             
    Serial.println(a);

    if (a >= 0 && a <= 18){
      one(a);
    }
    else if(a > 18 && a <= 36){
      two(a);
    }
    else if(a > 36 && a <= 54){
      three(a);
    }
    else if(a > 54 && a <= 72){
      four(a);
    }
    if (rec[0] == 1){
      if (pointer[0] == 0){
        one(18);
        pointer[0] == 1;
      }
      else{
        one(0);
        pointer[0] = 0;
      }
    }

    if (rec[0] == 2){
      if (pointer[1] == 0){
        two(36);
        pointer[1] = 1;
      }
      else{
        two(18);
        pointer[1] = 0;
      }
    }

    if (rec[0] == 3){
      if (pointer[2] == 0){
        three(54);
        pointer[2] = 1;
      }
      else {
        three(36);
        pointer[2] = 0;
      }
    }

    if (rec[0] == 4){
      if (pointer[3] == 0){
        four(72);
        pointer[3] = 1;
      }
      else{
        four(54);
        pointer[3] = 0;
      }
    }
}

void one(int a){
  
     delay(15);
      A=a;
     servo1.write(A*10);       
      delay(5);
}

void two(int a){
  
      B=a-18; 
      servo2.write(B*10);        
      delay(15);
}
void three(int a){
      C=a-36; 
      servo3.write(C*10);        
      delay(15);
}

void four(int a){

      D=a-54; 
      servo4.write(D*10);       
      delay(15);
}


void action(int receiveNum){
  for(int i = 0; i < receiveNum; i++){
    rec[i] = Wire.read();
  }
}
