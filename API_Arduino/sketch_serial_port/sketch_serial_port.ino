int counter = 0;

// Definimos el pin al que está conectado el LED
const int ledPin = 7;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Enviar datos por Puerto Serial
  Serial.println(++counter, DEC); // DEC: Se envia dato en formato decimal. Otros formatos podrían ser HEX (hexadecimal), OCT (octal), o BIN (binario).

  delay(3000);
  
  // Verificamos si hay datos disponibles en el puerto serial
  if (Serial.available() > 0) {
    // Leemos el primer byte recibido
    char command = Serial.read();

    // Si el comando es '1', encendemos el LED
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido");
    } 
    // Si el comando es '0', apagamos el LED
    else if (command == '0') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado");
    }
  }

}
