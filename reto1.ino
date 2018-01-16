//Allan Otárola Villalobos
//Reto1
//Curso Computación Física: Prototipos Interectivos 2

/*
Descripción:
Simulación de sistema de Alarma, que está emitiendo un sonido mientras la fotocelda reciba un rango de valor de luz menor A 30. Además un led rojo y azul que se encienden y apagan intermitente
mientras la alarma está activada.

 */

//Definición de variables

int pinRojo = 3;// declaración de variable para controlar el pin 3 que representa el led rojo
int pinAzul = 5;// declaración de variable para controlar el pin 5 que representa el led azul
int piezo = 6;// declaración de variable para controlar el pin 6 que representa el piezo
int fotocelda = 0;// declaración de variable para controlar el pin 0 que representa la fotocelda

void setup() {
  
  pinMode(pinRojo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(pinAzul,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(piezo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(fotocelda,INPUT);// configurando el pin con un funcionamiento de sensor, por eso el parámetro de entrada (INPUT)
  
  Serial.begin (9600);//configurando el monitor serial a 9600 baudios

}

void loop() {

  
//Ciclo que mantine la alarma encendida mientras los valores de la fotocelda sean menores a 30


 
  while(analogRead(fotocelda)< 30){//Ciclo que verifica que los valores de la fotocelda sea menores a 30, haciendo la consulta a través de la instrucción digitalRead

    Serial.println(analogRead(fotocelda));//Imprime en el monitor serial el valor del sensor de la fotocelda
    
    digitalWrite(pinRojo,HIGH);//Enciende el led Rojo
    digitalWrite(pinAzul,LOW);//Apaga el led Azul
    delay(100);//Un espera
    
    digitalWrite(pinRojo,LOW);//Apaga el led Rojo
    digitalWrite(pinAzul,HIGH);//Enciende el le Azul
    delay(100);//Un espera 

    tone (piezo,300,100);//Activa un sonido el el piezo
    delay(100);//Un espera 
    
  }

//Ciclo que mantine la alarma apagada mientras los valores de la fotocelda sean mañores a 30

  while(analogRead(fotocelda)> 30){//Ciclo que verifica que los valores de la fotocelda sea mayores a 30, haciendo la consulta a través de la instrucción digitalRead
    
    digitalWrite(pinRojo,LOW);//Apaga el led Rojo
    digitalWrite(pinAzul,LOW);//Apaga el led Azul

    Serial.println(analogRead(fotocelda));//Imprime en el monitor serial el valor del sensor de la fotocelda
  }

}
