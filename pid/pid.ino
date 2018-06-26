
/********************************************************
 * Sistema pêndulo-hélice
 * PID 
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
//tempo de duração do Setpoint variavel ( Quadrado e rampa )
#define tempo 100
double Setpoint, Input, Output;
int contador=0; // contador que auxilia calculo de setpoint variavel
float contf=0; // contador float para Seno

//Specify the links and initial tuning parameters
// Parametros do PID Kp, Ki, Kd, açao direta
 PID myPID(&Input, &Output, &Setpoint,0.7,1.5, 0.2 , DIRECT);
//PID myPID(&Input, &Output, &Setpoint,5,2, 3 , DIRECT);

//// Funções de Setpoint /////////
void quadrada(int &contador){
  if (contador <tempo){
    Setpoint=415;
    contador++;}
   else if(contador<2*tempo){
    Setpoint=590;
    contador++;
    }
    else contador=0;
  }
void onda(int &contador){
  int dif=(590-415)/tempo;
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
    Setpoint=sin(contf)*175+460;
    contf+=0.02;
    }
    else if (contador<20){
      Setpoint=sin(contf)*175+460;
      contf+=0.02;
      }
     else contf=0;
  }
/////////////// fim de funções de Setpoint ///////////
void setup()
{
  Serial.begin(9600);

  Input = analogRead(0);
  //
  // 90 º 590 
  //45 º 415
  // 0 º 240
  // º  
  Setpoint=590;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
}
int i=0;
// Filtragem de entrada, Quantidade de amostras
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
	//calculo do PID
  myPID.Compute();
  
  ////// Parte de conversão para  plotagem 
  double GrauAtual,GrauSetpoint,Tensao;
  GrauAtual=(Input-240)/3.888888888888888;
  GrauSetpoint=(Setpoint-240)/3.888888888888888;
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
//////////////// fim da saida serial para plotar ///

  // wait 
 
  analogWrite(3,Output);
  delay(10);

}

