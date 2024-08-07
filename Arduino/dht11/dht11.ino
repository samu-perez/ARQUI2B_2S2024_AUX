#include <DHT.h>

#define DHT_TYPE DHT11
#define DHT_PIN 9

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(2000);
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if(isnan(humedad) || isnan(temperatura)){
    Serial.println("No se reconocen datos en el sensor DHT11");
    return;
  }

  //Serial.print("Humedad: ");
  /*Serial.print(humedad);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");*/

  int humedadRandom = random(0, 100); // Genera un número aleatorio entre 0 y 100
  Serial.print("HUMEDAD/");
  //Serial.println(humedadRandom);
  Serial.println(humedad);
  delay(100);

}
