#include <Servo.h>

Servo servoGauche;
int facteurDirection = 3;
void setup() {
  Serial.begin(115200); //Si Baud plus faible, le servo ne marchera pas bien (il aura des sacades !!! :o :o)
  servoGauche.attach(10);
}

void loop() {

  if (Serial.available() > 0) {
    // Lire une ligne complète (terminée par \n)
    String input = Serial.readStringUntil('\n');
    int rotVolant = (input.toInt() / facteurDirection) + 90; 

    // Contrainte la valeur entre 0 et 180 pour le servo
    rotVolant = constrain(rotVolant, 0, 180);

    servoGauche.write(rotVolant);
  }
}