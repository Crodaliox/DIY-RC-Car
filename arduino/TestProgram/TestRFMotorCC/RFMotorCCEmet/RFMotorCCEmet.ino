#include <SPI.h>
#include <RF24.h>

#define pinCE   3           // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  4           // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre



RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel
String vitesseCCStr = "";
String input = "";
int vitesseCC = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné

  //CONFIG
  radio.setPALevel(RF24_PA_HIGH);    //Valeur d'alimentation du module
  radio.setDataRate(RF24_250KBPS); //Débit d'envoie

  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
}

void loop() {
  

  if (Serial.available()) {

    input = Serial.readStringUntil('\n');
    
    int sep = input.indexOf(';');

    if (sep != -1) {
      vitesseCCStr = input.substring(sep + 1);
      vitesseCC = vitesseCCStr.toInt();

      radio.write(&vitesseCC, sizeof(vitesseCC));
      delay(5);   // petite pause entre les transmissions
    }
  }
}
