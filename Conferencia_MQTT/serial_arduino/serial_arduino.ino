
void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
}

void loop() {
  int numeroAleatorio = random(10, 20); // Genera un número aleatorio entre 10 y 19
  
  Serial.write(numeroAleatorio);
  //Serial.println(numeroAleatorio);

  delay(5000);
}
