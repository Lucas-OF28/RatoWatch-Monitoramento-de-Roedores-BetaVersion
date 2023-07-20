#include <LiquidCrystal.h>
 
// Ligações do Arduino
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
const int pinoSensor = 8; // PINO DIGITAL UTILIZADO PELA SAÍDA DO SENSOR
const int pinoLed = 10; // PINO DIGITAL UTILIZADO PELO LED
int contador = 0; // Variável para contar as vezes que o LED pisca
int comprimento = 40; // Comprimento percorrido em centímetros
bool ledAceso = false; // Estado atual do LED
bool ledDesligadoAnterior = true; // Estado anterior do LED
unsigned long tempoInicial = 0; // Tempo inicial em milissegundos
unsigned long tempoAtual = 0; // Tempo atual em milissegundos
unsigned long tempoDecorrido = 0; // Tempo decorrido em milissegundos
float distanciaTotal = 0.0; // Distância total percorrida em metros
float velocidadeMedia = 0.0; // Velocidade média em metros por segundo
 
void setup() {
  Serial.begin(9600); // INICIALIZA A SERIAL
  lcd.begin(16, 2); // Inicializa o display LCD com 16 colunas e 2 linhas
  pinMode(pinoSensor, INPUT); // DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT); // DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); // LED INICIA DESLIGADO
  tempoInicial = millis(); // Captura o tempo inicial
  lcd.setCursor(0, 0); // Posiciona o cursor na coluna 0, linha 0
  //lcd.print("Voltas: 0"); // Inicializa o display com a contagem de voltas
  lcd.setCursor(0, 1); // Posiciona o cursor na coluna 0, linha 1
  //lcd.print("Distancia: 0m"); // Inicializa o display com a distância total
}
 
void loop() {
  static int comprimentoTotal = 0; // Variável para armazenar o comprimento total percorrido
 
  if (digitalRead(pinoSensor) == HIGH) { // SE LEITURA DO PINO FOR IGUAL A 1 (HIGH), FAZ
    digitalWrite(pinoLed, HIGH); // ACENDE O LED
    ledAceso = true; // Atualiza o estado do LED
  } else { // SENÃO, FAZ
    digitalWrite(pinoLed, LOW); // APAGA O LED
    ledAceso = false; // Atualiza o estado do LED
  }
 
  if (ledAceso && ledDesligadoAnterior) { // Detecta a transição de desligado para ligado
    contador++; // Incrementa o contador
    comprimentoTotal += comprimento; // Acrescenta o comprimento ao comprimento total
    ledDesligadoAnterior = false; // Atualiza o estado anterior do LED
  } else if (!ledAceso) { // Atualiza o estado anterior do LED quando estiver desligado
    ledDesligadoAnterior = true;
  }
 
  if (ledAceso) { // Atualiza o display somente quando o LED estiver aceso
    tempoAtual = millis(); // Captura o tempo atual
    tempoDecorrido = tempoAtual - tempoInicial; // Calcula o tempo decorrido em milissegundos
    distanciaTotal = (float)comprimentoTotal / 100.0; // Converte a distância total de centímetros para metros
    velocidadeMedia = (float)comprimentoTotal / (float)tempoDecorrido * 1000.0 / 100.0; // Calcula a velocidade média em metros por segundo
 
    lcd.setCursor(1, 0); // Posiciona o cursor na coluna 7, linha 0
    lcd.print("V:"); // Atualiza a contagem de voltas no display
    lcd.print(contador); // Atualiza a contagem de voltas no display    
 
    lcd.setCursor(7, 0); // Posiciona o cursor na coluna 10, linha 1    
    lcd.print(distanciaTotal); // Atualiza a distância total no display    
    lcd.print(" m"); // Atualiza a distância total no display
 
    // lcd.print("Distancia"); // Limpa o restante da linha
 
    if (velocidadeMedia >= 0.0) { // Verifica se a velocidade média é um valor válido
      lcd.setCursor(1, 2); // Posiciona o cursor na coluna 12, linha 0
      lcd.print(velocidadeMedia); // Atualiza a velocidade média no display
      lcd.print(" m/s"); // Exibe o texto "Velocidade:"
    }
  }
}
