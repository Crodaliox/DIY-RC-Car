#include <SPI.h>
#include <RF24.h>

#define tunnel "PIPE1"

RF24 radio(3,4);
const byte adresse[6] = tunnel; // Mise au format "byte array"
const char message[] = "Hello World";
String vitesseCCStr = "";
String input = "";
int vitesseCC = 0;

void setup()
{
    Serial.begin(115200);
    
    if (!radio.begin())
    {
        Serial.println("NRF absent");
        while(1);
    }

    Serial.println("NRF détecté !");
    radio.printDetails();

    Serial.println("3 - NRF24 détecté OK");

    //radio.setAutoAck(false); Pour tester seulement l'emetteur
    radio.openWritingPipe(adresse); 
    radio.setPALevel(RF24_PA_HIGH); 
    radio.stopListening(); 
    Serial.println("4 - Setup terminé");
}

void loop(){
  //Serial.println("5 - Dans la boucle"); 
  input = Serial.readStringUntil('\n');
    
    int sep = input.indexOf(';');

    if (sep != -1) {
      vitesseCCStr = input.substring(sep + 1);
      vitesseCC = vitesseCCStr.toInt();
    }
    
  if(radio.write(&vitesseCC, sizeof(vitesseCC))){ 
    Serial.println("Message envoyé "); 
    Serial.println(vitesseCC); } 
    //delay(100);
}