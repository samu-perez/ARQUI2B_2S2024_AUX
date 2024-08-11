#include <EEPROM.h>

/* Conceptos uso de Memoria EEPROM
1 celda -> 1 byte
0 a 255 en decimal
00000000 - 11111111 en binario
decimal 65 = 'A' -> 1000001 en binario

CHAR: 1 byte
INT: 2 bytes
FLOAT: 4 bytes

*/


// Definir la dirección de inicio en la EEPROM para almacenar los datos de los sensores
#define EEPROM_START_TEMPERATURA 0
#define EEPROM_START_HUMEDAD 10
#define EEPROM_START_LUZ 20
#define EEPROM_START_CO2 30
#define EEPROM_START_PROXIMIDAD 40

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

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  guardarDTH11(temperatura, humedad);
  leerDTH11();

}

void guardarDTH11(float temperatura, float humedad){
  EEPROM.put(EEPROM_START_TEMPERATURA, temperatura);  //Escribir (direccion_inicial, valor)
  EEPROM.put(EEPROM_START_HUMEDAD, humedad);  //Escribir (direccion_inicial, valor)
}

void leerDTH11(){
  float tempMemoria;
  float humedadMemoria;

  EEPROM.get(EEPROM_START_TEMPERATURA, tempMemoria);  //Obtener (direccion_inicial, var_almacenar)
  Serial.println(tempMemoria);
  EEPROM.get(EEPROM_START_HUMEDAD, humedadMemoria);  //Obtener (direccion_inicial, var_almacenar)
  Serial.println(humedadMemoria);
  delay(100);
}
