import processing.serial.*; // Comunicacion con Arduino

Serial puertoArduino;
int humedadArduino = 0;

void setup() {
  size(400, 400);  // Tamaño del lienzo
  
  puertoArduino = new Serial(this, "COM3", 9600);
  puertoArduino.bufferUntil('\n'); // Separador de valores en el Buffer
  
}

void draw() {
  background(255);  // Fondo blanco
  
  dibujarGotas(humedadArduino);
}

// Definir la función que contiene el código
void dibujarGotas(int humedad) {
  
  // Dibujar la gota de agua
  fill(0, 0, 255, humedad);  // Componente azul cambia con el valor
  //noStroke();  // Sin contorno
  
  ellipse(width / 2, height / 2, 110, 145);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 2, height / 2, 90, 140);  // Cambia las dimensiones según tus necesidades
  
  ellipse(width / 4, height / 2, 55, 95);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 4, height / 2, 40, 90);  // Cambia las dimensiones según tus necesidades
  
  ellipse(width / 1.3, height / 2, 55, 95);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 1.3, height / 2, 40, 90);  // Cambia las dimensiones según tus necesidades
  
  fill(0); // Color del texto (negro en este caso)
  textSize(25); // Tamaño del texto
  text("Porcentaje de humedad: " + humedad + "%", 50, height - 70);
  
  delay(1000);
  
}

void serialEvent(Serial p) {
  String datosArduino = puertoArduino.readString();
  println("datosArduino: " + datosArduino);
  
  String[] datosSensor =  splitTokens(datosArduino, "/\n\r");
  printArray(datosSensor);
  println(datosSensor[0]);
  println(int(datosSensor[1]));
  
  int valorSensor = int(datosSensor[1]);
  
  if (datosSensor[0].equals("HUMEDAD")) {
    //println("Porcentaje de Humedad: " + valorSensor);
    humedadArduino = valorSensor;
    
  } 
  
}
