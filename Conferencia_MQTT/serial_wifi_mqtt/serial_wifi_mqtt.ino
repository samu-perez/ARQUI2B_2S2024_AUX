
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Crear objetos para la conexión WiFi y MQTT
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Definir las credenciales de WiFi
String ssid     = "Samuel";
String password = "samuel123";

// Variables para controlar los intentos de conexión WiFi
byte cont_intentos = 0;
byte max_intentos = 50;

// Definir el servidor MQTT y el puerto de conexión
char *server = "broker.emqx.io";
int port = 1883;

// Variable para almacenar el resultado como cadena
String resultS = "";

// Buffer para almacenar datos convertidos antes de enviarlos por MQTT
char bufferPublish[10];

void setup() {
    // Inicializa la comunicación Serial a 115200 baudios
    Serial.begin(115200);
    Serial.println("\n");

    // Inicializa la conexión WiFi y MQTT
    wifiInit();
    mqttClient.setServer(server, port); // Configura el servidor MQTT
    mqttClient.setCallback(callback);   // Define la función callback para manejar los mensajes recibidos

    // Comentar si no se requiere esperar a Serial
    //while(!Serial){;}
}

void loop() {
    // Verifica si la conexión MQTT está activa, si no, intenta reconectar
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();  // Mantiene la conexión MQTT activa

    // ** Comunicación NodeMCU (ESP8266) con el puerto Serial del Arduino **
    if(Serial.available()){
      // Lee los datos del puerto serial
      int valorArduino = Serial.read();
      Serial.println("valorArduino: ");
      Serial.println(valorArduino);
      
      // Convierte el valor leído de int a cadena de caracteres
      itoa(valorArduino, bufferPublish, 10);

      // Publica el valor convertido en el tópico MQTT
      mqttClient.publish("topic/temperatura_G100", bufferPublish);
      delay(100); // Retardo para evitar el envío rápido de múltiples mensajes
    }

    // ** Bloque de prueba de números aleatorios para simular datos (comentar si no es necesario) **
    /*int numeroAleatorio = random(10, 20); // Genera un número aleatorio entre 10 y 19
    Serial.println(numeroAleatorio);

    itoa(numeroAleatorio, bufferPublish, 10); // Convierte el número en una cadena de caracteres

    mqttClient.publish("topic/temperatura_G100", bufferPublish);
    delay(5000);*/
}


void wifiInit(){
    // Inicia el proceso de conexión a la red WiFi
    WiFi.begin(ssid, password);

    // Intentar conectar hasta un máximo de 50 veces
    while (WiFi.status() != WL_CONNECTED and cont_intentos < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
        cont_intentos++;
        delay(500);
        Serial.print(".");
    }

    Serial.println("");

    // Si la conexión es exitosa, imprime detalles de la red
    if (cont_intentos < max_intentos) {
        Serial.println("********************************************");
        Serial.print("Conectado a la red WiFi: ");
        Serial.println(WiFi.SSID());
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("macAdress: ");
        Serial.println(WiFi.macAddress());
        Serial.println("*********************************************");
    } // Si no se puede conectar, muestra un mensaje de error
    else {
        Serial.println("------------------------------------");
        Serial.println("Error de conexion");
        Serial.println("------------------------------------");
    }
}


// Función que se ejecuta cuando se recibe un mensaje en un tópico suscrito
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido - Topic [");
    Serial.print(topic);
    Serial.print("] ");

    // Convertir el payload recibido (en bytes) a una cadena de caracteres
    char payload_string[length + 1];
    memcpy(payload_string, payload, length);    // Copia los datos del payload - params: guardar_destino, origen, tamaño
    payload_string[length] = '\0';              // Añade el terminador de cadena
    
    // Convertir la cadena de caracteres recibida a entero
    int resultI = atoi(payload_string);

    Serial.println();
    Serial.print("resultI:");
    Serial.println(resultI);

    // Bloque opcional para guardar el payload recibido como una cadena (comentar si no es necesario)
    /*resultS = "";
    
    for (int i=0;i<length;i++) {
        resultS= resultS + (char)payload[i];
    }
    Serial.println();
    Serial.println(resultS);*/
}


void reconnect() {
    // Intentar reconectar al servidor MQTT en caso de que la conexión se haya perdido
    while (!mqttClient.connected()) {
        Serial.print("Intentando conectarse MQTT...");

        // Si la conexión MQTT es exitosa
        if (mqttClient.connect("arduinoClient")) {
            Serial.println("Conectado");

            // Suscribirse al tópico MQTT "topic/<IDENTIFICADOR>" - No necesariamente se debe suscribir a tópicos cuando se conecta
            mqttClient.subscribe("topic/motor_G100");
        
        } else {  // Si falla la conexión, mostrar el estado y esperar 5 segundos antes de intentar nuevamente
            Serial.print("Fallo, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" intentar de nuevo en 5 segundos");
            delay(5000);
        }
    }
}
