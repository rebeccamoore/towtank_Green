#include <DualVNH5019MotorShield.h>
double kP = 100.0;
double kD = 0.5;
double kI = 1.0;
double v;
double vD;
double vError;
double vErrorLast;
double vErrorIntegral = 0;
byte dummy = B0000000;
int incomingByte = 0;
boolean changed;

unsigned long loopStart;  //the time of the beginning of the last loop

unsigned long timeStepMicros = 5000;

unsigned long timeMicros;


double command;

DualVNH5019MotorShield md;


double getVelocity(){
  double offsetVoltage;
  double RPM;
  const double V2RPM = 0.00225;
  const double VEL2RPM = 324.676;
  double velocity;

  offsetVoltage = analogRead(4)*5.0/1024.0 - 2.5;

  RPM = (offsetVoltage*4.0)/V2RPM;

  velocity = RPM/VEL2RPM;

  return velocity;

}

void changeParameters(){
  Serial.println("IN CONSTRUCTION");

}

double changeSpeed(double vD){
  Serial.println("Press (+) to increase vD and (-) to decrease (in 0.1 in/s increments)");
  Serial.println("Press (N) to negate");
  Serial.println("Press (E) to exit");
  int incomingByte = 0;
  while(incomingByte != 69){
    if(Serial.available() > 0) {
      incomingByte = Serial.read();
    }
    if(incomingByte == 0){
    }
    else if(incomingByte == 43){
      vD += 0.1;
      Serial.print("vD = ");
      Serial.println(vD);
      incomingByte = 0;
    }
    else if(incomingByte == 45){
      vD -= 0.1;
      Serial.print("vD = ");
      Serial.println(vD);
      incomingByte = 0;
    } 
    else if(incomingByte == 78){
      vD = vD*-1.0;
      Serial.print("vD = ");
      Serial.println(vD);
      incomingByte = 0;
    }
    else if(incomingByte == 69){
      Serial.println("EXITING");
    }
    else{
      Serial.println("Not a recognized command");
      Serial.println("Press (+) to increase vD and (-) to decrease (in 0.1 in/s increments)");
      Serial.println("Press (N) to negate");
      Serial.println("Press (E) to exit");
      incomingByte = 0;
    } 
  }
  return vD;
}


void setup(){
  Serial.begin(115200);
  md.init();
  vD = 1.0;
  loopStart = micros();
}

void loop(){
  incomingByte = 0;
  vErrorIntegral = 0.0;
  Serial.print("The current desired speed is ");
  Serial.print(vD);
  Serial.println(" (in/s).");
  Serial.print("The current kP is ");
  Serial.println(kP);
  Serial.print("The current kD is ");
  Serial.println(kD);
  Serial.print("The current kI is ");
  Serial.println(kI);
  Serial.println("Press capital s (S) to start the tracking");
  Serial.println("Press capital c (C) to change speed");
  Serial.println("Press capital u (P) to update PID gains");

  while(incomingByte == 0){  
    if(Serial.available() > 0) {
      incomingByte = Serial.read();
    }
  }

  if(incomingByte == 67){
    vD = changeSpeed(vD);
  }

  else if (incomingByte == 80){
    changeParameters();
  }

  else if(incomingByte == 83){  

    loopStart = micros();

    while(incomingByte == 83){
      if(Serial.available() > 0) {
        incomingByte = Serial.read();
      }

      loopStart += timeStepMicros;

      v = getVelocity();
      vError = vD - v;

      command = kP*(vError) + kD*(vErrorLast - vError)/(timeStepMicros/1000000.0) + kI*vErrorIntegral;

      md.setM1Speed(command);

      //      Serial.print("V=");
      Serial.println(v);
      //      Serial.print("C=");
      //      Serial.println(command);


      vErrorLast = vError;
      vErrorIntegral += vError;

      timeMicros = micros();
      dummy = B00000000;
      if (timeMicros < (loopStart+timeStepMicros)){
        while(micros() < (loopStart + timeStepMicros)){
          //timeMicros = micros();
          dummy = B11111111;
          //delayMicroseconds(0);
        }
      }
      Serial.println(dummy);
    }
  }

  else{
    Serial.println("INCORRECT COMMAND");
  }

  md.setM1Speed(0);

}


