#include <Servo.h>
  int rightDrivePin = 8;
  int leftDrivePin = 9;
  int deadbandPercent = 10;
  int radioMaxChange = 450;
  int radioAvg = 16650;
  
  Servo driveRight, driveLeft;
void setup() {
  driveRight.attach(rightDrivePin);
  driveLeft.attach(leftDrivePin);
  //input signal from RC reciever
  pinMode(2, INPUT);//input of thrust (speed forward) level from controller
  pinMode(3, INPUT);//turn (rotation) input level from controler
  pinMode(4, INPUT); // Set pin 4 as input from RC reciever, controls
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int radioForwards = pulseIn(2, LOW);
  int radioTurn = pulseIn(3, HIGH);

  int radioForwardsPercent = (long)(radioForwards - radioAvg) * 100 / radioMaxChange;

  if(abs(radioForwardsPercent) < 10) {
    radioForwardsPercent = 0;
  }
  if(radioForwardsPercent > 100) {
    radioForwardsPercent = 100;
  }
  if(radioForwardsPercent < -100) {
    radioForwardsPercent = -100;
  }
  
  Serial.print("radioForwards: ");
  Serial.println(radioForwardsPercent);

}
void startRightMotor(int speedPercent) {
  if(speedPercent == 0) {
    rightMotor.detach(rightMotorPin);
  }
  else {
    if(!rightMotor.attached()) {
      rightMotor.attach(rightMotorPin);
    }
    rightMotor.write(90 + (speedPercent * 0.9));
  }
}
void startLeftMotor(int speedPercent) {
  if(speedPercent == 0) {
    leftMotor.detach(leftMotorPin);
  }
  else {
    if(!leftMotor.attached()) {
      leftMotor.attach(leftMotorPin);
    }
    leftMotor.write(90 + (speedPercent * 0.9));
  }
}
/*
class {
  int pin;
  Servo servo;
  public:
  Motor(int pin) {
    servo.attach(pin);
  }
  void Run(int speedPercent) {
    if(speedPercent == 0) {
      servo.detach(pin);
    }
    else {
      if(!servo.attached()) {
        servo.attach(pin);
      }
      servo.write(90 + (speedPercent * 0.9));
    }
  }
}
*/
