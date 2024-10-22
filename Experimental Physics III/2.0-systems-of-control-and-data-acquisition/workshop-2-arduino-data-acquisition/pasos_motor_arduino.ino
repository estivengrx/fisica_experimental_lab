#include <Stepper.h>

// Número de pasos por revolución para tu motor
const int pasosPorRevolucion = 2066;  // Pasos para 360° que calculamos con interpolación lineal

// Inicializa el motor de paso ingresando los pines de las señales en orden: IN4, IN2, IN3, IN1
Stepper miMotor(pasosPorRevolucion, 23, 13, 5, 12);

void setup() {
  // Establece la velocidad del motor (en RPM)
  miMotor.setSpeed(10);
  // Inicializa la comunicación serial
  Serial.begin(115200);
}

void loop() {
  // Mueve el motor una revolución en una dirección
  Serial.println("Moviendo una revolución en sentido horario");
  miMotor.step(pasosPorRevolucion);
  delay(1000);

  // Mueve el motor una revolución en la otra dirección
  Serial.println("Moviendo una revolución en sentido antihorario");
  miMotor.step(-pasosPorRevolucion);
  delay(1000);
}