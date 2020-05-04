#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

AF_DCMotor motorL(3);
AF_DCMotor motorR(4);
const int rxpin = A0; // 接收 pin
const int txpin = A1; // 發送 pin
SoftwareSerial bluetooth(rxpin, txpin);
Servo frontservo;

void setup() {
  motorL.setSpeed(200);
  motorL.run(RELEASE);
  motorR.setSpeed(200);
  motorR.run(RELEASE);

  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("Serial ready");
  bluetooth.begin(9600);
  bluetooth.setTimeout(100);
  Serial.println("Bluetooth ready");

  frontservo.attach(10);
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
    motorL.run(RELEASE);
    motorR.run(RELEASE);
    Serial.println("stop");
  }
  else if(command==2) {
    motorL.run(FORWARD);
    motorR.run(FORWARD);
    Serial.println("forward");
  }
  else if(command==3) {
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
    Serial.println("backward");
  }
  else if(command==4) {
    frontservo.write();
    delay(1000);
    Serial.println("left");
  }
  else if(command==5) {
    frontservo.write();
    delay(1000);
    Serial.println("right");
  }
}
