int in1 = 8;
int in2 = 7;


void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
}

void loop() {

  digitalWrite(in1,0);
  digitalWrite(in2,0);
  delay(3000);

  digitalWrite(in1,1);
  digitalWrite(in2,0);
  delay(3000);

  digitalWrite(in1,0);
  digitalWrite(in2,0);
  delay(3000);

  digitalWrite(in1,0);
  digitalWrite(in2,1);
  delay(3000);

}
