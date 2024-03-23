# uhf_reader_AT
Routine for R200 Invelion UHF reader/writer
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
