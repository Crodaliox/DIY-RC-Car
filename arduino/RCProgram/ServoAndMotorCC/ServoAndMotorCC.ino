#include <Servo.h>

Servo servoDirection;

int facteurDirection = 3;

// Servo
int servoPin = 10;

// CC Motor (L298n)
int in1 = 7;
int in2 = 8;
int ENA = 9;

int vitesse = 0;

void setup() {

  Serial.begin(115200);

  servoDirection.attach(servoPin);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // sens de rotation moteur
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
}

void loop() {

  if (Serial.available() > 0) {

    // Lecture des valeurs envoyé par le programme C++ de récupération de valeur du volant
    String input = Serial.readStringUntil('\n');

    //En trouve l'emplacement du séparateur dans la chaine de caractère (Si plusieurs séparateur, renseignez la valeur de départ dans le deuxieme attribut)
    int sep = input.indexOf(';');

    // séparation des valeurs
    String rotStr = input.substring(0, sep);
    String vitesseStr = input.substring(sep + 1);

    //Conversion String to Int
    int rotVolant = rotStr.toInt();
    vitesse = vitesseStr.toInt();

    // Conversion pour le servo
    int angleServo = (rotVolant / facteurDirection) + 90;
    angleServo = constrain(angleServo, 0, 180);

    servoDirection.write(angleServo);
    analogWrite(ENA, vitesse);
  }
}