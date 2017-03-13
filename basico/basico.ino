#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial bt (2,13); // RX, TX
String datoserial; 
#define trigPin 10
#define echoPin 9
int rangomax=200;
int rangomin=0;
int mover=0;
long tiempo, distancia;


AF_DCMotor motora(1, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm delantero izquierdo
AF_DCMotor motorb(2, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm delantero derecho
AF_DCMotor motorc(3, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm Trasero izquierdo
AF_DCMotor motord(4, MOTOR12_64KHZ); // crear motor #2, 64KHz pwm Trasero derecho
 
void setup() {
  Serial.begin(9600);          
  Serial.println("ArduBot_UDD");
  bt.begin(38400);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  tiempo = pulseIn(echoPin, HIGH);
  distancia= (tiempo/2) / 29.1;
  
  
if (distancia<=20){
    
    mov_fow(244,11,1250);
    
Serial.println(distancia);

  } else {
    
      //// INICIO LECTURA SERIAL
 while (bt.available()) {
  datoserial = bt.readString();
  
  Serial.println(datoserial);  
  String velocidad = separar(datoserial, '+', 0);
  String accion = separar(datoserial, '+', 1);
  String tiempo = separar(datoserial, '+', 2);
    String emer_stop = separar(datoserial, '+', 3);

  
  int velocidadint = velocidad.toInt();
  int accionint = accion.toInt();
  int tiempoint = tiempo.toInt();
  
   mov_fow(velocidadint,accionint,tiempoint);
   
   } // FIN LECTURA SERIAL
   
   
    Serial.println(distancia);
  }
  
  

}


int mov_fow (int velocidad,int direccion, int tiempo){
  motora.setSpeed(velocidad); //min 200 - max 255
  motorb.setSpeed(velocidad);//min 200 - max 255
  motorc.setSpeed(velocidad);//min 200 - max 255
  motord.setSpeed(velocidad);//min 200 - max 255 
  
  //ADELANTE
  if (direccion==0){
    motora.run(BACKWARD);  
    motorb.run(FORWARD);
    motorc.run(FORWARD);
    motord.run(FORWARD);
    delay(tiempo);
    
  //ATRAS 
  } else if (direccion==1){
    motora.run(FORWARD);  
    motorb.run(BACKWARD);
    motorc.run(BACKWARD);
    motord.run(BACKWARD);
     delay(tiempo);
  }
  //DERECHA
  else if (direccion==2){
    motora.run(BACKWARD);  
    motorb.run(BACKWARD);
    motorc.run(FORWARD);
    motord.run(BACKWARD);
   delay(tiempo);
    
  }
  
  //IZQUIERDA
    else if (direccion==3){
    motora.run(FORWARD);  
    motorb.run(FORWARD);
    motorc.run(BACKWARD);
    motord.run(FORWARD);
  delay(tiempo);
    
  }
  
     else if (direccion==10){
    motora.setSpeed(0); //min 200 - max 255
  motorb.setSpeed(0);//min 200 - max 255
  motorc.setSpeed(0);//min 200 - max 255
  motord.setSpeed(0);//min 200 - max 255 
    
  }
  
       else if (direccion==11){
    motora.setSpeed(244); //min 200 - max 255
  motorb.setSpeed(244);//min 200 - max 255
  motorc.setSpeed(244);//min 200 - max 255
  motord.setSpeed(244);//min 200 - max 255 
   motora.run(BACKWARD);  
    motorb.run(BACKWARD);
    motorc.run(FORWARD);
    motord.run(BACKWARD);
   delay(1250);
    
    
  }
  
  //motora.RELEASE();
  motora.setSpeed(0); //min 200 - max 255
  motorb.setSpeed(0);//min 200 - max 255
  motorc.setSpeed(0);//min 200 - max 255
  motord.setSpeed(0);//min 200 - max 255 
}
  


 String separar(String datos, char separador, int inicial)
{
 int found = 0;
  int strIndex[] = {0, -1  };
  int maxIndex = datos.length()-1;
  for(int i=0; i<=maxIndex && found<=inicial; i++){
  if(datos.charAt(i)==separador || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>inicial ? datos.substring(strIndex[0], strIndex[1]) : "";
}



