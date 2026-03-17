int in1 = 8;
int in2 = 7;

int ENA = 10; // La pin ENA de la puce LN298n sert à controler la vitesse du moteur (Valeur compris entre 0 et 255)

int vitesse = 0;

void setup() {
  Serial.begin(115200);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ENA, OUTPUT);

  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void loop() {
  //Lecture de la valeur envoyé par le programme C++ et séparation du ;
  String input = Serial.readStringUntil('\n');
  int sep = input.indexOf(';');

  String vitesseStr = input.substring(sep + 1);
  vitesse = vitesseStr.toInt();
  analogWrite(ENA, vitesse);
}
