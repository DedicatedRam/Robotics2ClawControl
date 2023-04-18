#include <Servo.h>
Servo base;
Servo claw;
Servo up_down;
Servo front_back;
int randomNum;
int clawUpperBound = 155;
int clawLowerBound = 0;
int armHeightUpperBound = 155;
int armHeightLowerBound = 0;
int forwardbackUpperBound = 170;
int forwardbackLowerBound = 0;
int leftrightUpperBound = 150;
int leftrightLowerBound = 0;




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
      case 'w': 
        if(up_down.read()>= forwardbackUpperBound){
          Serial.println("This arm cannot go any more forward");          
        }else{
          up_down.write(up_down.read() + 5);
        }
        break;
      case 's':
        if(up_down.read()<=forwardbackLowerBound){
          Serial.println("This arm cannot go any more backward");
        }else{
          up_down.write(up_down.read() - 5);          
        }
        break;
      case 'a': 
        if(front_back.read()>= leftrightUpperBound){
          Serial.println("This arm cannot rotate anti-clockwise anymore");
        } else{
          front_back.write(front_back.read() + 5);
        }
        break;
      case 'd':
        if(front_back.read()<=leftrightLowerBound){
          Serial.println("This arm cannot rotate clockwise anymore");
        }else{
          front_back.write(front_back.read() - 5);
        }
        break;
      case 'q': 
        if(base.read()>=armHeightUpperBound){
          Serial.println("The arm cannot ascend any more");
        }else{
          base.write(base.read() + 5);
        }
        break;
      case 'e':
        if(base.read()<=armHeightLowerBound){
          Serial.println("The arm cannot descend any more");
        }else{
          base.write(base.read() - 5);
        }
        break;
      case 'z': 
        if(claw.read()>=clawUpperBound){
          Serial.println("The claw cannot close any further");
        }else{
          claw.write(claw.read() + 5);
        }
        break;
      case 'x':
        if(claw.read()<=clawLowerBound){
          Serial.println("The claw cannot open any further");
        }else{
          claw.write(claw.read() - 5);
        }
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
