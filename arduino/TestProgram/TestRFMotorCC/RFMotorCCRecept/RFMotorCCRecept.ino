#include <SPI.h>
#include <RF24.h>

#define pinCE   3             // On associe la broche "CE" du NRF24L01 à la sortie digitale D3 de l'arduino
#define pinCSN  4             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D4 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

//CCMotor
int in1 = 8;
int in2 = 7;
int ENA = 10; // La pin ENA de la puce LN298n sert à controler la vitesse du moteur (Valeur compris entre 0 et 255)

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
char message[32] = "";
int VitesseCC = 0;

void setup() {
  //Setup moteur cc
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ENA, OUTPUT);

  digitalWrite(in1,1);
  digitalWrite(in2,0);

  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  // Serial.begin(115200);
  // Serial.println("Récepteur NRF24L01");
  // Serial.println("");

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné

  //CONFIG
  radio.setPALevel(RF24_PA_LOW);      //Alimentation du module
  radio.setDataRate(RF24_250KBPS); //Débit d'envoie
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {
    radio.read(&VitesseCC, sizeof(VitesseCC));                        // Si un message vient d'arriver, on le charge dans la variable "message"
    // Serial.print("Message reçu : "); Serial.println(VitesseCC);     // … et on l'affiche sur le port série
    analogWrite(ENA, VitesseCC);
  }
}