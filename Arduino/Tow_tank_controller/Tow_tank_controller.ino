#include <DualVNH5019MotorShield.h>



DualVNH5019MotorShield md;
double offsetVoltage;
double RPM;
const double V2RPM = 0.00225;
const double VEL2RPM = 324.676;
double velocity;
int loopStart;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  }
}

double velocityControl(double desiredV, DualVNH5019MotorShield motorDriver){
  double offsetVoltage;
  double RPM;
  const double V2RPM = 0.00225;
  const double VEL2RPM = 324.676;
  double velocity;
  
  offsetVoltage = analogRead(4)*5.0/1024.0 - 2.5;
      
  RPM = (offsetVoltage*4.0)/V2RPM;

  velocity = RPM/VEL2RPM;

  if(desiredV > 0){
    if(desiredV > velocity){
      motorDriver.setM1Speed(100);

      
      Serial.print("F ");
      Serial.println(velocity);
    }
    else{
      motorDriver.setBrakes(0,0);
      Serial.print("C ");
      Serial.println(velocity);      
    }
  }
  
  
  if(desiredV < 0){
    if(desiredV < velocity){
      motorDriver.setM1Speed(-100);
      Serial.print("B ");
      Serial.println(velocity);
    }
    else{
      Serial.print("C ");
      Serial.println(velocity);
      motorDriver.setBrakes(0,0);
    }
  }
  
  
    
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();

}

void loop()
{
  for(int i = 0; i < 10; i++){
  loopStart = millis();
  while((millis() - loopStart) < 6000)
  {
    velocityControl(1.00, md);  
  }
  
  md.setBrakes(400,400);
  delay(2000);
  
  loopStart = millis();
  while((millis() - loopStart) < 6000)
  {
    velocityControl(-1.00, md);  
  }
  
  md.setBrakes(400,400);
  delay(2000);
  }
  
}


