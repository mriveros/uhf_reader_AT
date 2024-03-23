/*
Escrito por Sichuan Rui Pin Technology Co., Ltd.
Copiar y utilizar conservando los derechos de autor.
*/


/* Lectura múltiple de comandos */
unsigned char ReadMulti[10] = {0XAA,0X00,0X27,0X00,0X03,0X22,0XFF,0XFF,0X4A,0XDD};
unsigned int timeSec = 0;
unsigned int timemin = 0;
unsigned int dataAdd = 0;
unsigned int incomedate = 0;
unsigned int parState = 0;
unsigned int codeState = 0;


void setup() {
  // Configuración del puerto serie y del LED
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); // Configurar la velocidad del puerto serie a 115200 baudios
  Serial.println("Hola mundo.");// "Hola mundo."
  Serial.write(ReadMulti,10);
}

void loop() {

  // Leer el comando en un intervalo de tiempo
  timeSec ++ ;
  if(timeSec >= 50000){
    timemin ++;
    timeSec = 0;
    if(timemin >= 20){
      timemin = 0;
      // Enviar comando de lectura múltiple
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write(ReadMulti,10);
      digitalWrite(LED_BUILTIN, LOW); 
    }
  }
 
  if(Serial.available() > 0)// Se reciben datos por el puerto serie
  {
    // Respuesta recibida, a continuación se muestra un ejemplo de lectura de tarjeta
    //AA 02 22 00 11 C7 30 00 E2 80 68 90 00 00 50 0E 88 C6 A4 A7 11 9B 29 DD 
    /*
    AA: Cabecera del marco
    02: Código de instrucción
    22: Parámetro de instrucción
    00 11: Longitud de datos de instrucción, 17 bytes
    C7: Potencia de señal RSSI
    30 00: Código de PC de la etiqueta: Registro de información relacionada con el fabricante de la etiqueta
    E2 80 68 90 00 00 50 0E 88 C6 A4 A7: Código EPC
    11 9B: Comprobación CRC
    29: Comprobación
    DD: Final del marco 
    */
    incomedate = Serial.read();// Obtener los datos recibidos por el puerto serie
    // Comprobar si corresponde al código de instrucción
    if((incomedate == 0x02)&(parState == 0))
    {
      parState = 1;
    }
    // Comprobar si corresponde al parámetro de instrucción
    else if((parState == 1)&(incomedate == 0x22)&(codeState == 0)){  
        codeState = 1;
        dataAdd = 3;
    }
    else if(codeState == 1){
      dataAdd ++;
      // Obtener RSSI
      if(dataAdd == 6)
      {
        Serial.print("RSSI:"); 
        Serial.println(incomedate, HEX); 
        }
       // Obtener el código PC
       else if((dataAdd == 7)|(dataAdd == 8)){
        if(dataAdd == 7){
          Serial.print("PC:"); 
          Serial.print(incomedate, HEX);
        }
        else {
           Serial.println(incomedate, HEX);
        }
       }
       // Obtener el EPC, si es necesario procesarlo, se puede hacer aquí
       else if((dataAdd >= 9)&(dataAdd <= 20)){
        if(dataAdd == 9){
          Serial.print("EPC:"); 
        }        
        Serial.print(incomedate, HEX);
       }
       // Desbordamiento de posición, volver a recibir
       else if(dataAdd >= 21){
        Serial.println(" "); 
        dataAdd= 0;
        parState = 0;
        codeState = 0;
        }
    }
     else{
      dataAdd= 0;
      parState = 0;
      codeState = 0;
    }
  }
}
