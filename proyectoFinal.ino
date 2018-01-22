//Allan OtÃ¡rola Villalobos
//Proyecto final
//Curso ComputaciÃ³n FÃ­sica: Prototipos Interectivos 2



//LibrerÃ­as

#include <LiquidCrystal.h>//LibrerÃ­a que controla la pantalla LCD
#include <OneWire.h>//Se importa la biblioteca que controla el sensor de temperatura sumergible.
#include "paraMelodia.h"//LibrerÃ­a que contiene definiciones para la reproducciÃ³n de las notas 


//DefiniciÃ³n de variables y objetos

LiquidCrystal lcd(8,9,4,5,6,7);//DefiniciÃ³n de los pines que usa la pantalla LCD

int DS18S20_Pin = 3; //DefiniciÃ³n de variable "DS18S20" que representa la seÃ±al del pin digital 3

OneWire ds(DS18S20_Pin);  // Se crea un ejemplar "ds" de la clase OneWire conectado en el Pin 3 digital.

int piezo = 2;
int abanico = 13;
int fotocelda = A0;
int lampara = 11;

int cantidadLuz = 0;

int estadoAbanico = 0;
int estadoInicial = 1;


//DefiniciÃ³n de los arreglos con los que se van a reproducir las notas para la meldÃ­a
//CÃ³digo que se extrae de http://www.iescamp.es/miarduino/2016/02/15/buzzer-y-star-wars/

int melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};


//DefiniciÃ³n de variables necesarias para reproducir la melodÃ­a
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

  Serial.begin (9600);//configurando el monitor serial a 9600 baudios

  pinMode(piezo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parÃ¡metro de salida (OUTPUT)
  pinMode(abanico,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parÃ¡metro de salida (OUTPUT)
  pinMode(fotocelda,INPUT);// configurando el pin con un funcionamiento de sensor, por eso el parÃ¡metro de entrada (INPUT)
  pinMode(lampara,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parÃ¡metro de salida (OUTPUT)

   
  //ConfiguraciÃ³n de la pantalla LCD
  
    
     //Ciclo que reproduce la melodÃ­a  
     for (int i=0; i<MAX_COUNT; i++) {
      lcd.setCursor(4,1);
      lcd.print("Cargando...");
      lcd.noBlink();
      toneM = melody1[i];
      beat = beats1[i];
      duration = beat * tempo;
      playTone();//Llamada de la funciÃ³n que reproduce los tonos
      delayMicroseconds(pause);
    }
    
}

void loop() {

   cantidadLuz = analogRead(fotocelda);
 
   
   float temperature = getTemp(); //Se guarda el valor que obtiene el sensor y se guarda en la variable "temperature" puede tardar 2 segundos en ejecutarse.

   Serial.print("Temperatura del agua: "); // Se imprime en el monitor serial el valor de la variable de temperatura.
   Serial.println(temperature); // Se imprime en el monitor serial el valor de la variable de temperatura.
   
   Serial.print("LUZ: ");
   Serial.println(cantidadLuz);

   //Reporte de la distancia en la pantalla LCD
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.print(temperature);
   lcd.print(" Luz:");
   lcd.println(cantidadLuz);
   

   activarAbanico(temperature);//Procedimiento que activa el abanico
   luces(cantidadLuz);//Procedimiento que activa las luces o las apaga

}

//Definición del procedimiento que activa el abanico
void activarAbanico(float temperature){

  if (temperature > 28 && estadoAbanico == 0){
    
      digitalWrite(abanico,HIGH);    
      estadoAbanico = 1;
  }
  else{

    if (temperature <= 28 && temperature > 1 ){

      digitalWrite(abanico,LOW);
      
      estadoAbanico = 0;
    }
    
   
  }

}

//Definición del procedimiento que controla las luces
void luces(int cantidadLuz){

  if (cantidadLuz > 400){

    digitalWrite(lampara,HIGH);
  
  }
  else{
    digitalWrite(lampara,LOW);
    
  
  }

}



//FunciÃ³n para obtener temperatura

float getTemp(){ //FunciÃ³n que calcula la temperatura en grados centÃ­grados
  
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC no es vÃ¡lido!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("El dispositivo no se reconoce");
      return -1000;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // inicia la conversiÃ³n
  
  delay(1000); // Espera para que la conversiÃ³n de temperatura se complete

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); //
  
  for (int i = 0; i < 9; i++) { 
    data[i] = ds.read();
  }
  
  ds.reset_search();
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB);
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;// se retorna el valor de la temperatura en grados centÃ­grados 
}


//Procedimiento que reproduce los tonos de la melodÃ­a
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
