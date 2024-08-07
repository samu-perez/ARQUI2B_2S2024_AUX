void setup() {
  size(400, 400);  // Tamaño del lienzo
  //size(800, 800);  // Tamaño del lienzo
  //fullScreen();    //Pantalla Completa
  
}

void draw() {
  background(255);  // Fondo blanco
  
  //fill(r, g, b): Color de relleno en formato RGB
  fill(150, 200, 100); 
  
  //dibujarFormas();
  //dibujarCirculoMouse();
  dibujarGotas();
  
}

void dibujarFormas(){
  //rect(x, y, width, height): Dibuja un rectángulo.
  rect(50, 50, 100, 150);
  
  //fill(r, g, b, alpha): Color con transparencia
  fill(150, 200, 100, 150);
  
  //ellipse(x, y, width, height): Dibuja una elipse.
  ellipse(200, 100, 80, 80);
  
  //stroke(r, g, b): Color de contorno.
  stroke(50, 100, 200);
  
  ellipse(300, 100, 80, 50);
  
  //line(x1, y1, x2, y2): Dibuja una línea.
  line(300, 50, 350, 150);
  line(300, 50, 300, 150);
}

void dibujarCirculoMouse(){
  float ellipseSize = dist(mouseX, mouseY, pmouseX, pmouseY);
  
  // Dibuja un círculo con el tamaño calculado
  fill(150, 200, 100, 150);
  ellipse(mouseX, mouseY, ellipseSize, ellipseSize);
  
  // Muestra el valor de ellipseSize en la pantalla
  fill(0); // Color del texto (negro en este caso)
  textSize(20); // Tamaño del texto
  
  //text(c, x, y)
  text("Tamaño del círculo: " + ellipseSize, 20, height - 20);
}

// Definir la función que contiene el código
void dibujarGotas() {
  int  intensidadHumedad = int(random(1, 101));
  
  // Dibujar la gota de agua
  fill(0, 0, 255, intensidadHumedad);  // Componente azul cambia con el valor
  //noStroke();  // Sin contorno
  
  ellipse(width / 2, height / 2, 110, 145);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 2, height / 2, 90, 140);  // Cambia las dimensiones según tus necesidades
  
  ellipse(width / 4, height / 2, 55, 95);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 4, height / 2, 40, 90);  // Cambia las dimensiones según tus necesidades
  
  ellipse(width / 1.3, height / 2, 55, 95);  // Cambia las dimensiones según tus necesidades
  ellipse(width / 1.3, height / 2, 40, 90);  // Cambia las dimensiones según tus necesidades
  
  fill(0); // Color del texto (negro en este caso)
  textSize(25); // Tamaño del texto
  text("Porcentaje de humedad: " + intensidadHumedad + "%", 50, height - 70);
  
  delay(1000);
  
}
