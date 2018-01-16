//Allan Otárola Villalobos
//Práctica Dirigida 1
//Curso Computación Física: Prototipos Interectivos 2

/*
Descripción:
Simulación de sistema de Alarma, que está emitiendo un sonido mientras el botón no está presionado. Además un led rojo y azul que se encienden y apagan intermitente
mientras la alarma está activada.

 */

//Definición de variables

int pinRojo = 3;// declaración de variable para controlar el pin 3 que representa el led rojo
int pinAzul = 5;// declaración de variable para controlar el pin 5 que representa el led azul
int piezo = 6;// declaración de variable para controlar el pin 6 que representa el piezo
int boton = 2;// declaración de variable para controlar el pin 2 que representa el botón

void setup() {
  
  pinMode(pinRojo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(pinAzul,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(piezo,OUTPUT);// configurando el pin con un funcionamiento de actuador, por eso el parámetro de salida (OUTPUT)
  pinMode(boton,INPUT);// configurando el pin con un funcionamiento de sensor, por eso el parámetro de entrada (INPUT)
  
  Serial.begin (9600);//configurando el monitor serial a 9600 baudios

}

void loop() {

  
//Ciclo que mantine la alarma encendida mientras no esté presionado el botón

  while(digitalRead(boton)==0){//Ciclo que verifica que el botón no está presionado, haciendo la consulta a través de la instrucción digitalRead

    Serial.println(digitalRead(boton));//Imprime en el monitor serial el estado del botón que puede ser 0 o 1
    
    digitalWrite(pinRojo,HIGH);//Enciende el led Rojo
    digitalWrite(pinAzul,LOW);//Apaga el led Azul
    delay(100);//Un espera
    
    digitalWrite(pinRojo,LOW);//Apaga el led Rojo
    digitalWrite(pinAzul,HIGH);//Enciende el le Azul
    delay(100);//Un espera 

    tone (piezo,300,100);//Activa un sonido el el piezo
    delay(100);//Un espera 
    
  }


//Ciclo que mantine la alarma apagada mientras esté presionado el botón

  while(digitalRead(boton)==1){//Ciclo que verifica que el botón está presionado, haciendo la consulta a través de la instrucción digitalRead
    
    digitalWrite(pinRojo,LOW);//Apaga el led Rojo
    digitalWrite(pinAzul,LOW);//Apaga el led Azul

    Serial.println(digitalRead(boton));//Imprime en el monitor serial el estado del botón que puede ser 0 o 1
  }

}
