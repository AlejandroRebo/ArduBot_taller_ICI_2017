/*
ARDUBOT_UDD version simplificada de la version basica de concepcion.
Recepción de información de APP y movimiento de ArduBot Para realizar los movimientos del ArduBot se programo una función
con simples caracteres para un procesamiento mas rapido de las entradas.
parte de la optimizacion del codigo se saco tambien de:
https://www.youtube.com/watch?v=Ei43v93NEMQ
codigo ejemplo
https://www.dropbox.com/s/na4cw9atorjdjhm/Carro%20Inalambrico%20Bluetooth.txt?dl=0


Las acciones disponibles programadas son las siguientes:

a: Avanzar
b: Retroceder
c: Giro Derecha
d: Giro Izquierda
e: Freno total
f: más velocidad
l: menos velocidad
se pueden integrar mas caracteres para realizar mas acciones.
Además se instaló un sensor de distancia que permite al detectar una
distancia menor de 40 cm realiza un retroceso.
*/



#include <AFMotor.h> //libreria de motor de adafruit v1
#include <SoftwareSerial.h>
SoftwareSerial bt (2,13); // RX, TX recordar los pines 
//CONECTA DESDE EL HC-05 TX AL ARDUINO PIN DIGITAL 2. 
// CONECTA DESDE EL HC-05 RX AL ARDUINO PIN DIGITAL  13
#define trigPin 10
#define echoPin 9
long tiempo, distancia;
int estado = 'e';  
int VEL=100;
 
AF_DCMotor Motor1(1, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm delantero izquierdo
AF_DCMotor Motor2(2, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm delantero derecho
AF_DCMotor Motor3(3, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm Trasero izquierdo
AF_DCMotor Motor4(4, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm Trasero derecho
 
void setup() {
  Serial.begin(9600);          
  Serial.println("ArduBot_UDDvsimple test");
  bt.begin(38400); //lectura bluetooth
        
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
}


void loop() {   
        
        Motor1.setSpeed(VEL); //designamos la velocidad a cada motor este valor numerico se toma desde la variable global VEL
        Motor2.setSpeed(VEL);
        Motor3.setSpeed(VEL);
        Motor4.setSpeed(VEL);

        
  if (VEL >=255){ //esto permite controlar el exeso numerico de velocidad hace que al sumar mas de 255 quede en 255
  VEL=255;
  }
   if (VEL <= 0){ //similar si la resta llega a un numero negativo se mantiene en 0
  VEL=0;
  }

  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  tiempo = pulseIn(echoPin, HIGH);
  distancia= (tiempo/2) / 29.1;
 Serial.println(distancia); 
  
if (distancia<=40){
 
    
    
Serial.println("distancia menor que 40");
 Motor1.run(FORWARD);  //invertido, ahora tiene mas logica
 Motor2.run(BACKWARD);
 Motor3.run(BACKWARD);
 Motor4.run(BACKWARD);
 
delay(500);

Motor1.run(RELEASE);  //paro
Motor2.run(RELEASE);
Motor3.run(RELEASE);
Motor4.run(RELEASE);
delay(300);

  }
   
  if (bt.available()>=0){
    estado = bt.read();
   //estado = Serial.read();
  Serial.println(estado); 



  }
 
      if(estado == 'a' ) //Si si el bluethoot adelante es cuatro comandos
      {
      
         Serial.println("adelante");
         //forward es la orden hacia adelante
Motor1.run(FORWARD) ;
Motor2.run(FORWARD);
Motor3.run(FORWARD);
Motor4.run(FORWARD);
      }
 
      else if(estado == 'b') //test de atras
      {
       
         Serial.println("atras");
         //backward es igual a retroceder

Motor1.run(BACKWARD);
Motor2.run(BACKWARD);
Motor3.run(BACKWARD);
Motor4.run(BACKWARD);
         
      }
 
      else if(estado == 'c') //derecha
      {
         Serial.println("derecha");
         //derecha     
    Motor1.run(FORWARD);  //invertido, ahora tiene mas logica
    Motor2.run(BACKWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD);
¡
      }
       else if(estado == 'd') //izquierda
      {
         Serial.println("izquierda");
       //IZQUIERDA
        
    Motor1.run(BACKWARD);  //invertido, ahora tiene mas logica
    Motor2.run(FORWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD); 
      }
      
       else if(estado == 'e') //ayuda
      {
         Serial.println("paro");
           
Motor1.run(RELEASE); //paro
Motor2.run(RELEASE);
Motor3.run(RELEASE);
Motor4.run(RELEASE);
        
      }
    else if(estado == 'f') //más velocidad de la variable global
      {
         Serial.println("mas");
         VEL=VEL+20; //de esta forma sumamos a la variable global VEL 20 unidades mas arriba esta un codigo para limitar el numero
        
        
      }
      else if(estado == 'l') //menos velocidad de la variable global
      {
         Serial.println("menos"); 
       VEL=VEL-20; //de esta forma restamos a la variable global VEL 20 unidades mas arriba esta un codigo para limitar el numero
        
      }


}
 
