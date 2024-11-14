#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

/* Cria o objeto de controle para o display OLED. */
Adafruit_SSD1306 display(128, 64, &Wire);

/* Definir o pino do sensor IR. */
const int irSensorPin = 2;  // O pino digital onde o sensor IR está conectado.

int contador = 0;  // Variável para armazenar o contador.
bool irSensorState = LOW;  // Variável para armazenar o estado atual do sensor IR.
bool lastIrSensorState = LOW;  // Variável para armazenar o estado anterior do sensor IR.

void setup() {
  // Inicia o display OLED.
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  display.clearDisplay();
  
  // Configura o pino do sensor IR como entrada.
  pinMode(irSensorPin, INPUT);
  
  // Define o tamanho da fonte como o dobro do padrão.
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);  // Cor do texto (branco)
  
  // Exibe a mensagem inicial no display.
  //display.setCursor(0, 0);
  //display.print("Contador");
  //display.display();
  //delay(2000);  // Exibe a mensagem inicial por 2 segundos.
}

void loop() {
  // Lê o estado atual do sensor IR.
  irSensorState = digitalRead(irSensorPin);
  
  // Verifica se houve uma transição de LOW para HIGH (borda de subida).
  if (irSensorState == HIGH && lastIrSensorState == LOW) {
    // Incrementa o contador quando a borda de subida é detectada.
    contador++;
    
    // Exibe uma mensagem de feedback no display.
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Contador de");
    display.setCursor(0, 20);
    display.print("de Abelhas");
    display.setCursor(0, 40);
    display.print(contador);
    display.display();
    
    // Aguarda um momento para evitar múltiplas detecções rápidas.
    delay(10);  // Ajuste conforme necessário para o seu sensor IR.
  }
  
  // Atualiza o estado anterior do sensor IR.
  lastIrSensorState = irSensorState;
  
  // Aguarda um momento para que o display não atualize muito rapidamente.
  delay(10);  // Este delay aqui evita uma atualização muito rápida do display.
}
