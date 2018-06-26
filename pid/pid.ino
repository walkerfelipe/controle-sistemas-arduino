
/********************************************************
 * Sistema pêndulo-hélice
 * PID
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
#define tempo 100
double Setpoint, Input, Output;
int contador=0;
float contf=0;
//Specify the links and initial tuning parameters
 PID myPID(&Input, &Output, &Setpoint,0.7,1.5, 0.2 , DIRECT);
//PID myPID(&Input, &Output, &Setpoint,5,2, 3 , DIRECT);
void quadrada(int &contador){
  if (contador <tempo){
    Setpoint=645;
    contador++;}
   else if(contador<2*tempo){
    Setpoint=840;
    contador++;
    }
    else contador=0;
  }
void onda(int &contador){
  int dif=(840-645)/tempo;
  if (contador<tempo){
    Setpoint+=dif;
    contador++;
    }
    else if (contador<2*tempo){
      Setpoint-=dif;
      contador++;
      }
     else contador=0;
  }

void onda2(float &contf){
  if (contf<10){
    Setpoint=sin(contf)*370+460;
    contf+=0.02;
    }
    else if (contador<20){
      Setpoint=sin(contf)*370+460;
      contf+=0.02;
      }
     else contf=0;
  }

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
  Setpoint=645;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
}
  int i=0;
  int amostragem=100;

void loop()
{
  /* Descomentar apenas 1 dessas linhas 
   *  Onda quadrada, rampa , ou senoidal
   *  comentar todas as linhas para ter um Setpoint constante
   */
  //quadrada(contador);
  //onda(contador);
  //onda2(contf);
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
 
  analogWrite(3,Output);
  delay(10);

}

