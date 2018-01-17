//Allan Otárola Villalobos
//Reto número 2 Puerta automática
//Curso Computación Física: Prototipos Interectivos 2

/*
Descripción:
  Simulación de puerta automática que se abre cuando dectecta un objeto cerca y reproduce una melidía de arleta en el momento que se abre la puerta.
*/

//Librerías que se utilizan

#include <LiquidCrystal.h>
#include <Servo.h>
#include "paraMelodia.h"

//Definición de variables

Servo servo1;//Definición de un ejemplar de la clase Servo para poder controlar el servomotor

int trig = 13;// declaración de variable para controlar el pin 13
int echo = 12;// declaración de variable para controlar el pin 12 
float distanciaFinal;// declaración de variable para almacenar el calculo de la distancia
int servo = 3;// declaración de variable para controlar el pin 3
int piezo = 2;// declaración de variable para controlar el pin 2
int grados; //almacena ele estado en grados del servo
int tmp = 0; variable temporal que almacena el giro que debe hacer el servo
int pulsominimo = 650;//Giro mínimo en grados del servo
int pulsomaximo = 2550;////Giro máximo en grados del servo

LiquidCrystal lcd(8,9,4,5,6,7);//Definición de los pines con los que trabaja la LCD

//Definición de los arreglos con los que se van a reproducir las notas para la meldía
//Código que se extrae de http://www.iescamp.es/miarduino/2016/02/15/buzzer-y-star-wars/

int melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};


//Definición de variables necesarias para reproducir la melodía
//http://www.iescamp.es/miarduino/2016/02/15/buzzer-y-star-wars/

int MAX_COUNT = sizeof(melody1) / 2;
long tempo = 10000;
int pause = 1000;
int rest_count = 50;
int toneM = 0;
int beat = 0;
long duration  = 0;
int potVal = 0;



void setup() {

  //configuración de la pantalla LCD
  lcd.setCursor(4,1);
  lcd.print("PRONIE");
  lcd.noBlink();
  delay(2000);

  //Configuración de pines
  pinMode(trig,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(echo,INPUT);// configurando el pin con un funcionamiento de sensor, por eso el parámetro de entrada (INPUT)
  pinMode(piezo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)


  //Indicamos al servo motor, por cual pin se va comunicar y el ángulo menor y mayor
  servo1.attach (servo, pulsominimo,pulsomaximo); 
  
  
  Serial.begin (9600);//configurando el monitor serial a 9600 baudios

}

void loop() {

  distanciaFinal = calcularDistancia();// Llamada a la función que hace el cálculo de la distancia
  
  grados = servo1.read();Lectura del estado en grados del servo

  //Impresiones en el monitor serial
  Serial.print("Grados :");
  Serial.println(grados);
  delay(200);
  Serial.println("_ _ _ _ _ _ _ _");
  Serial.println("cm :");
  Serial.println(distanciaFinal);
  delay(200);


  if (distanciaFinal < 25){//Condicional que verifica si un objeto está cerca del ultrasónico

    tmp = 100;  
    servo1.write(tmp);//Al cumplirse la condición se giral el servo 100 grados

  
   //Ciclo que reproduce la melodía  
   for (int i=0; i<MAX_COUNT; i++) {
      toneM = melody1[i];
      beat = beats1[i];
      duration = beat * tempo;
      playTone();//Llamada de la función que reproduce los tonos
      delayMicroseconds(pause);
   }
  }
  else{
    
    tmp = 0;
  }
  servo1.write(tmp);//Se gira el motor a 0 grados
  
  //Se reporta la distancia en la LCD
  lcd.setCursor(1,1);
  lcd.print("Distancia");
  lcd.println(distanciaFinal);
}


//Función que calcula la distancia
int calcularDistancia (){

  long distancia;
  long duracion;

  digitalWrite(trig,LOW);
  delayMicroseconds(4);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duracion = pulseIn (echo,HIGH);
  duracion = duracion/2;
  distancia = duracion/29;
  return distancia; 

}

//Procedimiento que reproduce los tonos de la melodía
void playTone() {

  long elapsed_time = 0;
  
  if (toneM > 0) {
    while (elapsed_time < duration) {
      digitalWrite(piezo,HIGH);
      delayMicroseconds(toneM / 2);
      digitalWrite(piezo, LOW);
      delayMicroseconds(toneM / 2);
      elapsed_time += (toneM);
    }
  }
  else {
    for (int j = 0; j < rest_count; j++) {
      delayMicroseconds(duration);
    }
  }
}
