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

int temperatura;

void setup() {
  Serial.begin(9600);

  char ascci = 65;
  EEPROM.write(100, ascci);  //Escribir (direccion, valor)

  int temp = 28;
  EEPROM.put(0, temp);  //Escribir (direccion_inicial, valor)

}

void loop() {
  //Serial.println("Datos almacenados:");

  char valor = EEPROM.read(100);  //Leer (direccion)
  Serial.println(valor);

  EEPROM.get(EEPROM_START_TEMPERATURA, temperatura);  //Obtener (direccion_inicial, var_almacenar)
  Serial.println(temperatura);
  delay(1000);

}
