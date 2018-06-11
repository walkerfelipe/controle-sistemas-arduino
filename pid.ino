/********************************************************
 * Sistema pêndulo-hélice
 * PID
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
 PID myPID(&Input, &Output, &Setpoint,0.7,1.5, 0.2 , DIRECT);
//PID myPID(&Input, &Output, &Setpoint,5,2, 3 , DIRECT);
void setup()
{
  Serial.begin(9600);
  //initialize the variables we're linked to
  Input = analogRead(0);
  // 90 º 830 
  // 0 º 460
  //45 º 645
  Setpoint = 460;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}
int i=0;
int amostragem=100;
void loop()
{
  Input=0;
  for (i=0;i<amostragem;i++){
  Input += analogRead(0);
  }
  Input=Input/amostragem;

  myPID.Compute();
  Serial.print(Setpoint);
  Serial.print(" ");
  Serial.print(Input);
  Serial.print(" ");
  Serial.println(Output);
  
  analogWrite(3,Output);
}

