 /* Fichier:      HelloWorldNRF24L01-Recepteur
  Description:  Réception d'un message "Hello World" depuis un autre arduino nano, via un NRF24L01
  Auteur:       Passion-Électronique

  Librairie utilisée : https://github.com/nRF24/RF24

  Créé le 19.03.2021
*/
#include <SPI.h>
#include <RF24.h>

#define pinCE   2            // On associe la broche "CE" du NRF24L01 à la sortie digitale D3 de l'arduino
#define pinCSN  4             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D4 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

//CCMotor
int in1 = 8;
int in2 = 7;
int ENA = 10; // La pin ENA de la puce LN298n sert à controler la vitesse du moteur (Valeur compris entre 0 et 255)

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
char message[32] = "";
int vitesseCC = 0;

void setup() {
    //Setup moteur cc
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ENA, OUTPUT);

  digitalWrite(in1,1);
  digitalWrite(in2,0);


  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  Serial.println("Récepteur NRF24L01");
  Serial.println("");

  // Partie NRF24

  bool ok = radio.begin();
  Serial.println("2 - radio.begin() a répondu");   // Si tu ne vois JAMAIS ce message, radio.begin() est bloqué

  if (!ok) {
    Serial.println("ERREUR : NRF24 non détecté !");
    while (1) {}     // on bloque volontairement ici pour bien voir l'erreur
  }                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_HIGH);      // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {
    radio.read(&vitesseCC, sizeof(vitesseCC));                        // Si un message vient d'arriver, on le charge dans la variable "message"
    Serial.print("Message reçu : "); Serial.println(vitesseCC);     // … et on l'affiche sur le port série !
    analogWrite(ENA, vitesseCC);
  }
}