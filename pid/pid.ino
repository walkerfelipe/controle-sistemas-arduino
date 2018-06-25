
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
//  Serial.begin(9600);
  //initialize the variables we're linked to
 // Input = analogRead(0);
  //136º  1023
  // 90 º 830 
  //45 º 645
  // 0 º 460
  // - 111,89 º 0 
  Setpoint = 645;
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
  double GrauAtual,GrauSetpoint,Tensao;
  GrauAtual=(Input-460)/4.1111111111;
  GrauSetpoint=(Setpoint-460)/4.1111111111;
  Tensao=Output/51;
  //Serial.print(Setpoint);
  //Serial.print(" ");
  //Serial.println(Input);
  //Serial.print(" ");
  //Serial.println(Output);
  Serial.print(Setpoint);
  Serial.print(",");
  Serial.print(Input);
  Serial.print(",");
  Serial.print(Output);
  Serial.print(",");
  Serial.print(GrauAtual);
  Serial.print(",");
  Serial.print(GrauSetpoint);
  Serial.print(",");
  Serial.print(Tensao);
  Serial.print("\n");
  
  // wait 
 
  
//  char text[40];
//  int In,Se,Ou;
//  In=(int)Input;
//  Se=(int)Setpoint;
//  Ou=(int)Output;
//
//  sprintf(text,"%d,%d,%d\n",In,Se,Ou);
//  Serial.println(text);
  analogWrite(3,Output);
  delay(10);

}

