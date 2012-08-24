#include <DualVNH5019MotorShield.h>


DualVNH5019MotorShield md;


void setup(){
  Serial.begin(115200);
  Serial.println("");
  Serial.println("BEGIN");
  md.init();
  
  
}

void loop(){
  
  md.setM1Speed(-100);
  delay(200);
  md.setM1Speed(-200);
  delay(200);
  md.setM1Speed(-300);
  delay(200);
  
  for(int commandSpeed = -400; commandSpeed <= 0; commandSpeed+=25){
    md.setM1Speed(commandSpeed);
    delay(200);
    Serial.print(commandSpeed);
    Serial.print(" ");
    Serial.print(analogRead(4));
    Serial.print(" ");
    Serial.println(md.getM1CurrentMilliamps());
    delay(200);
  }
  
  
  md.setM1Speed(75);
  delay(1000);
  
  for(int commandSpeed = 50; commandSpeed <= 400; commandSpeed+=25){
    md.setM1Speed(commandSpeed);
    delay(200);
    Serial.print(commandSpeed);
    Serial.print(" ");
    Serial.print(analogRead(4));
    Serial.print(" ");
    Serial.println(md.getM1CurrentMilliamps());
    delay(200);
  }
  
  md.setM1Brake(0);
  while(1){}
  
  
  
}

