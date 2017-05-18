/* PARA ACTIVAR LA ENTRADA DE COMANDOS AT EN EL BLUETOOH , APRETAR BOTON AL ENCENDER
ver video https://www.youtube.com/watch?v=PFIqjEdr8zY&t=6s
 *  COMANDOS CLAVES PARA 
 *  
 *   AT+ NAME=LASARO //para cambiar nombre
 *  
 *   AT+PSWD=1234   //para cambiar contraseña
 *
 *sacado en parte de :
 *http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/
 */

#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
  // CONECTA DESDE EL HC-05 TX AL ARDUINO PIN DIGITAL 2. 
  // CONECTA DESDE EL HC-05 RX AL ARDUINO PIN DIGITAL  3  

 
char c = ' '; //dar espacio 
 
void setup()  //parte que se ejecuta al partir el arduino
{
    Serial.begin(9600); //ES LA VELOCIDAD DE COMUNICACION DEL ARDUINO
    Serial.println("ARDUINO ESTA LISTO");  // para agregar comados AT
    
    Serial.println("TENER PRESENTE EN EL MONITOR SERIAL NL & CR"); //esto se ve al costado del monitor serial 
 
    //LA VELOCIDAD DE COMUNICACION DEL  HC-05 POR DEFECTO DEL MODO AT ES 38400
    BTserial.begin(38400);  
}
 
void loop()
{
 
    // MANTIENE LA LECTURA DESDE EL HC-05 Y LO ENVIA AL MONITOR SERIAL DEL ARDUINO 
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
    // DESDE EL ARDUINO HACIA EL BLUETOOTH "INGRESO DE COMANDOS AT" 
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c);  
    }
 
}

