#include <string.h> 

#define sentido 2 // dando nome nos pinos do Arduino
#define pulso 3
#define enable 4

int velocidade = 99; // varia de 1 a 99

char resposta[25] = {"         "}; // Declarando um vetor de caracteres global (fica visivel para todas as funções) que receberá os dados brutos da comunicação serial.

void setup() {
  Serial.begin(9600);
  for (int i = 2; i < 5; i++) pinMode(i, OUTPUT); //Fazendo com que os pinos 2,3 e 4 sejam saída, para controlar o driver.
  digitalWrite(enable, LOW); // O pino Enable fica low para que o driver seja habilitado
}

void loop() {
  EscutaSerial(); // A função que irá ficar escutando a comunicação serial e irá inserir esses dados no vetor resposta
  Comando(); // A função que irá interpretar o comando escrito no vetor resposta[] e realizar a ação.
//  Serial.println(resposta); // Printa o resultado interpretado caso seja necessário debugar.
}

void EscutaSerial() { // Função que recebe os dados seriais e insere na string
  byte leitura, i = 0;
  leitura = 255;
  strcpy(resposta, "                  ");
  while (1) {  
    if (Serial.available() > 0) { 

      while (leitura != 10) {
        if (Serial.available() > 0) {
          leitura = Serial.read();
          //   Serial.print((char)leitura);
          if (leitura==10) break;
          resposta[i] = (char)leitura;
          i++;
        }
      }
      i = 0;
      break;
    }
  }
}

void Comando(){ //Função que interpreta o que está escrito no vetor resposta e transforma em um comando para o motor de passo.
  int passos;
  passos = atoi(strtok(resposta, " "));
  Serial.println(passos);
   passos < 0 ? digitalWrite(sentido,HIGH) : digitalWrite(sentido,LOW);
 for(int i = 0; i<abs(passos); i++){
    digitalWrite(pulso, HIGH);
    delay(100/velocidade);
    digitalWrite(pulso, LOW);
    delay(100 - velocidade);
  }
}