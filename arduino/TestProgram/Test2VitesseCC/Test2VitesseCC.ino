int in1 = 8;
int in2 = 7;

int ENA = 10; // La pin ENA de la puce LN298n sert à controler la vitesse du moteur (Valeur compris entre 0 et 255)

int vitesse = 0;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ENA, OUTPUT);

  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void loop() {
  vitesse = vitesse + 1;
  analogWrite(ENA, vitesse);
  delay(100);



}
