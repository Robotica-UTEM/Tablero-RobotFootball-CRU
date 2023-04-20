#include <TimeLib.h>
#include <TM1637Display.h>
#define PIN1  2
#define PIN2  3
#define PIN3  4
#define PIN4  5
#define PIN5  6
#define PIN6  7
#define PIN7  8
#define PIN8  9
#define COM1  10
#define COM2  11
#define COM3  12
#define COM4  13
#define TRIG1 A0
#define ECHO1 A1
#define TRIG2 A2
#define ECHO2 A3
#define CLK   A4
#define DIO   A5
#define tiempo_maximo 5 //minutos

TM1637Display display(CLK, DIO);

int UNO[] = {0,1,0,1,0,0,0,0};  
int DOS[] = {1,1,0,0,0,1,1,1};
int TRES[] = {1,1,0,1,0,0,1,1};
int CUATRO[] = {0,1,1,1,0,0,0,1};
int CINCO[] = {1,0,1,1,0,0,1,1};
int SEIS[] = {1,0,1,1,0,1,1,1};
int SIETE[] = {1,1,0,1,0,0,0,0};
int OCHO[] = {1,1,1,1,0,1,1,1};
int NUEVE[] = {1,1,1,1,0,0,1,1};
int CERO[] = {1,1,1,1,0,1,1,0};
int NUMERO_A_MOSTRAR[8];

int DURACION1;
int DISTANCIA1;
int DURACION2;
int DISTANCIA2;

int contador1 = 0;
int contador2 = 0;
int contador3 = 0;
int contador4 = 0;

long Tiempo_anterior = millis();
unsigned long Tiempo_actual = millis();

void setup() {
  display.setBrightness(5);   // establece nivel de brillo
  setTime(0,0,0,20,6,2020);
  
  pinMode(PIN1,OUTPUT);
  pinMode(PIN2,OUTPUT);
  pinMode(PIN3,OUTPUT);
  pinMode(PIN4,OUTPUT);
  pinMode(PIN5,OUTPUT);
  pinMode(PIN6,OUTPUT);
  pinMode(PIN7,OUTPUT);
  pinMode(PIN8,OUTPUT);
  pinMode(COM1,OUTPUT);
  pinMode(COM2,OUTPUT);  
  pinMode(COM3,OUTPUT);
  pinMode(COM4,OUTPUT);
  pinMode(TRIG1,OUTPUT);
  pinMode(ECHO1,INPUT);    
  pinMode(TRIG2,OUTPUT);
  pinMode(ECHO2,INPUT);
  
  digitalWrite(PIN1,LOW);
  digitalWrite(PIN2,LOW);
  digitalWrite(PIN3,LOW);
  digitalWrite(PIN4,LOW);
  digitalWrite(PIN5,LOW);
  digitalWrite(PIN6,LOW);
  digitalWrite(PIN7,LOW);
  digitalWrite(PIN8,LOW);
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,LOW);
  digitalWrite(TRIG1,LOW);
  digitalWrite(TRIG2,LOW);
}
////////////////////////////////////////////////////
////////////principal///////////////////////////////
////////////////////////////////////////////////////
void loop() {
  Tiempo_partida();
  
  Tiempo_actual = millis();
  if(Tiempo_actual - Tiempo_anterior > 3000){
    Lectura_Sensores();  
  } 
  mostrar_contadores();
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
void Tiempo_partida(){
  time_t t = now();     // obtiene fecha y horario
  int minuto = minute(t);
  int segundo = second(t);
  if(minuto == tiempo_maximo && segundo == 0){
    while(true){
      display.showNumberDecEx(tiempo_maximo, 0b01000000, false, 2, 0);
      display.showNumberDec(0, true, 2, 2);  
      mostrar_contadores();
    }
  }
  else{
    display.showNumberDecEx(minuto, 0b01000000, false, 2, 0);
    display.showNumberDec(segundo, true, 2, 2);
  }
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
void mostrar_contadores(){
  Seleccionar_numero(contador1);
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,LOW);
  Mostrar_numero();
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,HIGH);
  digitalWrite(COM3,HIGH);
  digitalWrite(COM4,HIGH);
  delay(3);
  Seleccionar_numero(contador2);
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,LOW);
  Mostrar_numero();
  digitalWrite(COM1,HIGH);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,HIGH);
  digitalWrite(COM4,HIGH);
  delay(3);
  Seleccionar_numero(contador3);
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,LOW);
  Mostrar_numero();
  digitalWrite(COM1,HIGH);
  digitalWrite(COM2,HIGH);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,HIGH);
  delay(3);
  Seleccionar_numero(contador4);
  digitalWrite(COM1,LOW);
  digitalWrite(COM2,LOW);
  digitalWrite(COM3,LOW);
  digitalWrite(COM4,LOW);
  Mostrar_numero();
  digitalWrite(COM1,HIGH);
  digitalWrite(COM2,HIGH);
  digitalWrite(COM3,HIGH);
  digitalWrite(COM4,LOW);
  delay(3);
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
void Lectura_Sensores(){
  digitalWrite(TRIG1, HIGH);
  delay(1);
  digitalWrite(TRIG1, LOW);
  DURACION1 = pulseIn(ECHO1, HIGH);
  DISTANCIA1 = DURACION1 / 58.2;

  digitalWrite(TRIG2, HIGH);
  delay(1);
  digitalWrite(TRIG2, LOW);
  DURACION2 = pulseIn(ECHO2, HIGH);
  DISTANCIA2 = DURACION2 / 58.2;

  if(DISTANCIA1 <= 10 && DISTANCIA1 >= 0){
    contador2 = contador2 + 1;
    Tiempo_anterior=Tiempo_actual;
    if(contador2 == 10){
      contador2 = 0;
      contador1 = contador1 + 1;
    }
  }

  if(DISTANCIA2 <= 10 && DISTANCIA2 >= 0){
    contador4 = contador4 + 1;
    Tiempo_anterior=Tiempo_actual;
    if(contador4 == 10){
      contador4 = 0;
      contador3 = contador3 + 1;
    }
  }
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
void Seleccionar_numero(int contador){
  switch(contador){
    case 0:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = CERO[i];
      }
      break;
    case 1:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = UNO[i];
      }
      break;
    case 2:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = DOS[i];
      }
      break;
    case 3:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = TRES[i];
      }
      break;
    case 4:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = CUATRO[i];
      }
      break;
    case 5:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = CINCO[i];
      }
      break;
    case 6:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = SEIS[i];
      }
      break;
    case 7:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = SIETE[i];
      }
      break;
    case 8:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = OCHO[i];
      }
      break;
    case 9:
      for(int i=0; i<8;i++){
        NUMERO_A_MOSTRAR[i] = NUEVE[i];
      }
      break;
  }
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
void Mostrar_numero(){
  if(NUMERO_A_MOSTRAR[0]==1){
    digitalWrite(PIN1,HIGH);    
  }
  else{
    digitalWrite(PIN1,LOW);
  }
  if(NUMERO_A_MOSTRAR[1]==1){
    digitalWrite(PIN2,HIGH);    
  }
  else{
    digitalWrite(PIN2,LOW);
  }
  if(NUMERO_A_MOSTRAR[2]==1){
    digitalWrite(PIN3,HIGH);    
  }
  else{
    digitalWrite(PIN3,LOW);
  }
  if(NUMERO_A_MOSTRAR[3]==1){
    digitalWrite(PIN4,HIGH);    
  }
  else{
    digitalWrite(PIN4,LOW);
  }
  if(NUMERO_A_MOSTRAR[4]==1){
    digitalWrite(PIN5,HIGH);    
  }
  else{
    digitalWrite(PIN5,LOW);
  }
  if(NUMERO_A_MOSTRAR[5]==1){
    digitalWrite(PIN6,HIGH);    
  }
  else{
    digitalWrite(PIN6,LOW);
  }
  if(NUMERO_A_MOSTRAR[6]==1){
    digitalWrite(PIN7,HIGH);    
  }
  else{
    digitalWrite(PIN7,LOW);
  }
  if(NUMERO_A_MOSTRAR[7]==1){
    digitalWrite(PIN8,HIGH);    
  }
  else{
    digitalWrite(PIN8,LOW);
  }
}
