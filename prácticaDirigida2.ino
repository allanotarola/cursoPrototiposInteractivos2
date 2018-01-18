//Allan Otárola Villalobos
//Práctica Dirigida 2
//Curso Computación Física: Prototipos Interectivos 2

/*
Descripción:
Mecanismo que simula una puerta automática que se activa por la proximidad de los objetos

 */
 
//Librerías

#include <LiquidCrystal.h>

#include <Servo.h>

Servo servo1;//Creación de un ejemplar de la clase Servo


//Definición de variables

int trig = 13;// declaración de variable para controlar el pin 13
int echo = 12;// declaración de variable para controlar el pin 12 
float distanciaFinal;// declaración de variable para almacenar el calculo de la distancia

int servo = 3;//Difinición de la variable que hace referencia el pin del servo
int piezo = 2;//Difinición de la variable que hace referencia el pin del parlante o piezo
int grados;//Varible que almacena el estado en grados del servo
int tmp = 0;//Variable temporal que almacena el giro que da el servo
int pulsominimo = 650;//Giro mínimo del servo 
int pulsomaximo = 2550;//Giro máximo del servo

LiquidCrystal lcd(8,9,4,5,6,7);//Definición de los pines que usa la pantalla LCD

void setup() {

  //Configuración de la pantalla LCD
  lcd.setCursor(4,1);
  lcd.print("PRONIE");
  lcd.noBlink();
  delay(2000);

  //Definición de pines con su respectivo funcionamiento.
  pinMode(trig,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(echo,INPUT);// configurando el pin con un funcionamiento de sensor, por eso el parámetro de entrada (INPUT)
  pinMode(piezo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)


  //Indicamos al servo motor, por cual pin se va comunicar y el ángulo menor y mayor
  servo1.attach (servo, pulsominimo,pulsomaximo); 
  
  
  Serial.begin (9600);//configurando el monitor serial a 9600 baudios

}

void loop() {

  distanciaFinal = calcularDistancia();//Llamada de función que calacula la distancia
  
  grados = servo1.read();//Lectura del estado del servo

  //Impresión en el monitor serial
  Serial.print("Grados :");
  Serial.println(grados);
  delay(200);
  Serial.println("_ _ _ _ _ _ _ _");
  Serial.println("cm :");
  Serial.println(distanciaFinal);
  delay(200);


  //Condicional que cierra o abre la puerta según la distancia de los objetos
  if (distanciaFinal < 25){

    tmp = 100;
    servo1.write(tmp);
    tone (piezo, 600, 100);
  }
  else{
    tmp = 0;
  }
  delay(10);
  servo1.write(tmp);

   //Reporte de la distancia en la pantalla LCD
   lcd.setCursor(1,1);
   lcd.print("Distancia: ");
   lcd.println(distanciaFinal);
}

//Función que clacula la distancia

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
