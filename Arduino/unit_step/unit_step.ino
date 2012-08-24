#include <DualVNH5019MotorShield.h>

DualVNH5019MotorShield md;

//int adc_readings[400];
//int time_readings[400];
long start_time;
int incomingByte = 0;
boolean start;
int top_speed;
long beforeTime;
long afterTime;


void setup(){
  Serial.begin(115200);
  Serial.println("ADC DATA");
  md.init();
}

void loop(){
  
  for(top_speed = -400; top_speed <= 400; top_speed+=50){
  
    Serial.print("START ");
    Serial.println(top_speed);
  
    start_time = micros();
    
    for(int i = 0; i < 200; i++){
      beforeTime = micros() - start_time;
      Serial.print(analogRead(4));
      afterTime = micros() - start_time;
      Serial.print(" ");
      Serial.print(beforeTime);
      Serial.print(" ");
      Serial.println(afterTime);
    }
    
    md.setM1Speed(top_speed);
    for(int i = 0; i < 500; i++){
      beforeTime = micros() - start_time;
      Serial.print(analogRead(4));
      afterTime = micros() - start_time;
      Serial.print(" ");
      Serial.print(beforeTime);
      Serial.print(" ");
      Serial.println(afterTime);
    }
    
    md.setM1Speed(0);
    
    for(int i = 0; i < 500; i++){
      beforeTime = micros() - start_time;
      Serial.print(analogRead(4));
      afterTime = micros() - start_time;
      Serial.print(" ");
      Serial.print(beforeTime);
      Serial.print(" ");
      Serial.println(afterTime);
    }
    
    Serial.println("END");
    delay(3000);
  }
  while(1){
  }
  
}
  
