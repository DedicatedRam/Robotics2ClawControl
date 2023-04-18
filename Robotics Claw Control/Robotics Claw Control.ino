#include <Servo.h>
#include <LeapC.h>
Servo base;
Servo claw;
Servo up_down;
Servo front_back;
int randomNum;

void setup() {
  Serial.begin(9600);
  up_down.attach(10);
  base.attach(9);
  claw.attach(11);
  front_back.attach(8);
  claw.write(155);
  randomSeed(analogRead(0));
  Serial.println("Press m to play");
}

void choosePaperFullMotion(){
  countDownThriceMotion();
  chooseRock();
}
void chooseRockFullMotion(){
  countDownThriceMotion();
  choosePaper();
}
void chooseScissorsFullMotion(){
  countDownThriceMotion();
  chooseScissors();
}
void countDownMotion(){ 
  delay(600);
  base.write(180);
  delay(600);
  base.write(0);
}
void countDownThriceMotion(){
  claw.write(150);
  countDownMotion();
  countDownMotion();
  countDownMotion();
  delay(600);
  base.write(95);
}
void choosePaper(){
  claw.write(150);
  delay(1000);
}
void chooseRock(){
  claw.write(0);
  delay(1000);
}
void chooseScissors(){
  claw.write(150);
  delay(500);
  claw.write(0);
  delay(500);
  claw.write(150);
  delay(500);
  claw.write(0);
  delay(500);
  claw.write(155);
  delay(1000);
}


void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    switch(input) {
      case 'm':
        randomNum = random(1, 4);
        Serial.println(randomNum);
        switch(randomNum){
          case 1:
            Serial.println("I play rock!");
            chooseRockFullMotion();
            break;
          case 2:
            Serial.println("I play paper!");
            choosePaperFullMotion();
            break;
          case 3:
            Serial.println("I play scissors!");
            chooseScissorsFullMotion();
            break;
        }
        break;
      case 'w': // Move up/down
        up_down.write(up_down.read() + 5);
        break;
      case 's':
        up_down.write(up_down.read() - 5);
        break;
      case 'a': // Move front/back
        front_back.write(front_back.read() + 5);
        break;
      case 'd':
        front_back.write(front_back.read() - 5);
        break;
      case 'q': // Rotate base
        base.write(base.read() + 5);
        break;
      case 'e':
        base.write(base.read() - 5);
        break;
      case 'z': // Open/close claw
        claw.write(claw.read() + 5);
        break;
      case 'x':
        claw.write(claw.read() - 5);
        break;
      case '#':
        Serial.print("Claw: ");
        Serial.print(claw.read());
        Serial.print(" Arm Height: ");
        Serial.print(base.read()); 
        Serial.print(" Left/Right: ");  
        Serial.print(front_back.read()); 
        Serial.print(" for/back: ");
        Serial.print(up_down.read());
        Serial.println();
        break;
    }
  }

}
