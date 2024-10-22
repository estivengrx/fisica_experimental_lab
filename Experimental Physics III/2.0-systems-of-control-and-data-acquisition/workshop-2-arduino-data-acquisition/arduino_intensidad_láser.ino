/*
 * Este programa ejecuta un barrido del motor de paso luego de recibir un comando. Los comands programados son:
 * p# Con este comando se indica cuantos pasos se desea girar el motor.
 * f Con este comando se muestra el valor del voltaje en la fotoresistencia.
 * s# Con este comando se inicia el barrido angular defido por el ángulo (grados) ingreado después del caracter 's'.
 * para cada paso el programa imprime el ángulo (respecto a la posición inicial) y el voltaje en la fotoresistencia asociado.
 * */
 
#include <Stepper.h>

// Calibración que encontramos:
const int stepsPerRevolution = 2066;

// Se inicializa el motor de paso ingresando los pines de las señales: IN1, IN2, IN3, IN4
Stepper myStepper(stepsPerRevolution, 23, 13, 5, 12);

//Variables para el barrido con valores por defecto
int angulo_barrido=70; 
int comenzar=0; //Esta variable es una bandera (flag) que se usa para indicar cuándo se debe iniciar el barrido.

#define puerto_fotoresistencia 2 //Foto-resistencia conectada al pin 2

void setup() {
  myStepper.setSpeed(10); //Velocidad angular del motor en RPM. Funciona siempre y cuando stepsPerRevolution esté bien calculado.
  Serial.begin(115200);
  pinMode(14,OUTPUT);
  digitalWrite(14,1);
  pinMode(23,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(12,OUTPUT);

}
void loop() {
     digitalWrite(13,HIGH);
    digitalWrite(23,LOW);
    digitalWrite(5,LOW);
    digitalWrite(12,LOW);
  if(Serial.available()>0){
    char caracter=Serial.read();
    if(caracter=='p'){
      int pasos=Serial.parseInt();
      myStepper.step(pasos);
    }else if(caracter=='f'){
      float voltage=analogRead(2)*3.3/4095.0;
      Serial.println(voltage);
    }else if(caracter=='s'){
      angulo_barrido=Serial.parseInt();
      comenzar=1;
    }
  }

  if(comenzar==1){//Si se activa el barrido
    comenzar=0; //Regresa la bandera de activación al estado inicial.
    float Npasos=stepsPerRevolution*(angulo_barrido/360.0); //Numero de pasos para girar "angulo_barrido".
    int N=int(Npasos); //Numero de iteraciones para el for siguiente
    for(int i=0;i<N;i++){ //Para cada iteracion se avanzará un paso
      float voltaje_fotoresistencia=analogRead(puerto_fotoresistencia)*3.3/4095.0;
      Serial.print(i*360.0/stepsPerRevolution);
      Serial.print(' ');
      Serial.println(voltaje_fotoresistencia);
      delay(100); //Tiempo entre pasos (necesario para asegurar que la foto resistencia se estabilice)
      myStepper.step(1);

    }


  }
}
