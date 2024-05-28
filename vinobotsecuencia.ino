#include <Servo.h>
#include <Stepper.h>

Servo servo1base;
Servo servo2base;
Servo servobrazo1;
Servo servobrazo2;
Servo servoef;
int pasos = 500;
int angle;
int us;

int valor1;
int valor2;
int valor3;
int valor4;
int valor5;

Stepper myStepper(pasos, 3, 7, 12, 13);

#define S0 0
#define S1 1
#define S2 2
#define S3 4
#define salidaSensor 8

//  frecuencias de los fotodiodos
int frecuenciaRojo = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int colorRojo;
int colorVerde;
int colorAzul;

void color(){
   // lectura de los valores de color utilizando filtros RGB
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  delay(10); // se pone para estabilizar el sensor
  frecuenciaRojo = pulseIn(salidaSensor, LOW);
  colorRojo = map(frecuenciaRojo, 28, 145, 255, 0);
  Serial.print("R = ");
  Serial.print(colorRojo);
 
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  delay(10); // se pone para estabilizar el sensor
  frecuenciaVerde = pulseIn(salidaSensor, LOW);
  colorVerde = map(frecuenciaVerde, 32, 160, 255, 0);
  Serial.print(" G = ");
  Serial.print(colorVerde);
 
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  delay(10); // se pone para estabilizar el sensor
  frecuenciaAzul = pulseIn(salidaSensor, LOW);
  colorAzul = map(frecuenciaAzul, 30, 150, 255, 0);
  Serial.print(" B = ");
  Serial.println(colorAzul);

}

void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(20); // rpm

  servo1base.attach(10);
  servo2base.attach(9);
  servobrazo1.attach(5);
  servobrazo2.attach(11);
  servoef.attach(6);

  pinMode(A2, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
 
  // se define salidaSensor como entrada
  pinMode(salidaSensor, INPUT);
 
  // se define la escala de frecuencia a 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  Serial.begin(9600);

  Serial.println("Setup completo");
}

void loop() {

  // put your main code here, to run repeatedly:
  
  
  color();
  if (colorRojo > 80 && colorAzul > 80 && colorVerde < colorRojo && colorVerde < colorAzul) {
    Serial.println(" - Detectado MORADO");
    valor1=servo1base.read();
    valor2=servo2base.read();
    Serial.println(valor1);
    Serial.println(valor2);
    Serial.println("Moviendo bases a 120");
    angle = 120; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servo1base.write(angle);
    angle = 180-120; // Ángulo deseado
    us = map(angle, 0, 180, 700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servo2base.write(angle);
    delay(1000);
    valor1=servo1base.read();
    valor2=servo2base.read();
    Serial.println(valor1);
    Serial.println(valor2);
    delay(1000);

    
    valor3=servobrazo1.read();
    Serial.println(valor3);
    Serial.println("Moviendo brazo1 a 160");
    angle = 160; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servobrazo1.write(angle);
    delay(1000);
    valor3=servobrazo1.read();
    Serial.println(valor3);
    delay(1000);


    valor4=servobrazo2.read();
    Serial.println(valor4);
    Serial.println("Moviendo brazo2 a 100");
    angle = 100; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servobrazo2.write(angle);
    delay(1000);
    valor4=servobrazo2.read();
    Serial.println(valor4);
    delay(1000);

    valor5=servoef.read();
    Serial.println(valor5);
    digitalWrite(A2,HIGH);
    Serial.println("Moviendo servoef a 100");
    servoef.write(100);
    delay(1000);
    valor5=servoef.read();
    Serial.println(valor5);
    delay(1000);
    Serial.println("mueve motor");
    myStepper.step(pasos);
    delay(1000);
    digitalWrite(A2,LOW);

  } else if (colorVerde > 100 && colorVerde > colorRojo && colorVerde > colorAzul) {
    Serial.println(" - Detectado VERDE");

    valor1=servo1base.read();
    valor2=servo2base.read();
    Serial.println(valor1);
    Serial.println(valor2);
    Serial.println("Moviendo bases a 100");
    angle = 100; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servo1base.write(angle);
    angle = 180-100; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servo2base.write(angle);
    delay(1000);
    valor1=servo1base.read();
    valor2=servo2base.read();
    Serial.println(valor1);
    Serial.println(valor2);
    delay(1000);

    
    valor3=servobrazo1.read();
    Serial.println(valor3);
    Serial.println("Moviendo brazo1 a 100");
    angle = 100; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servobrazo1.write(angle);
    delay(1000);
    valor3=servobrazo1.read();
    Serial.println(valor3);
    delay(1000);

  
    valor4=servobrazo2.read();
    Serial.println(valor4);
    Serial.println("Moviendo brazo2 a 150");
    angle = 150; // Ángulo deseado
    us = map(angle, 0, 180,  700, 2300); // Mapea el ángulo a microsegundos (ajusta los valores según tu servo)
    servobrazo2.write(angle);
    delay(1000);
    valor4=servobrazo2.read();
    Serial.println(valor4);
    delay(1000);

    valor5=servoef.read();
    Serial.println(valor5);
    digitalWrite(A2,HIGH);
    Serial.println("Moviendo servoef a 70");
    servoef.write(70);
    delay(1000);
    valor5=servoef.read();
    Serial.println(valor5);
    digitalWrite(A2,LOW);

    Serial.println("devuelve motor");
    myStepper.step(-pasos);
    // Agregar tiempo de inactividad para reducir la corriente
    delay(2000);

  }


  // Agregar tiempo de inactividad para reducir la corriente
  delay(3000);

  
}




