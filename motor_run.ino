#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

AF_DCMotor motor(3);

const int rxpin = A0; // 接收 pin
const int txpin = A1; // 發送 pin
SoftwareSerial bluetooth(rxpin, txpin);
Servo frontservo;
int angle = 0;
  
void setup() {
  motor.setSpeed(200);
  motor.run(RELEASE);
  
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("Serial ready");
  bluetooth.begin(9600);
  bluetooth.setTimeout(100);
  Serial.println("Bluetooth ready");

  frontservo.attach(10);
  pinMode(A2,OUTPUT);
  analogWrite(A2,0);
  pinMode(A3,OUTPUT);
  analogWrite(A3,0);
}
  
void loop() {
  int command = GetCommand();  
  ExecCommand(command);
}

int GetCommand() {
  int command = bluetooth.parseInt();
  return command;
}

void ExecCommand(int command){

  if(command==1) {
    motor.run(RELEASE);
   
    Serial.println("stop");
    analogWrite(A2,255);
    analogWrite(A3,255);
  }
  else if(command==2) {
    motor.run(FORWARD);
   
    Serial.println("forward");
    analogWrite(A2,0);
    analogWrite(A3,0);
  }
  else if(command==3) {
    motor.run(BACKWARD);
    
    Serial.println("backward");
    analogWrite(A2,0);
    analogWrite(A3,0);
    delay(500);
    analogWrite(A2,255);
    analogWrite(A3,255);
    delay(500);
  }
  else if (command==4){
    int angle = bluetooth.parseInt();
    Serial.println(angle); 
    frontservo.write(angle);
    }
}

  
    
    
        
