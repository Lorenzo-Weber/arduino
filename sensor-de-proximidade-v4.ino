#include <Ultrasonic.h>
 
bool ligado = false;
int a_tipo = -1;
int car_offset = 20;
int count = 0;

int nivel1 = 1;
int nivel2 = 2;

int secDebug = 0;

const int pinoBot = 2;
const int pinoBuz = 3;
const int trig = 4;
const int echo = 5;
const int LEDs[] = {8, 9, 10, 11, 12};
const int qtdLED = 5;

void tom(char pino, int frequencia, int duracao){
  float periodo = 1000.0/frequencia; //Periodo em ms
  for (int i = 0; i< duracao/(periodo);i++){ //Executa a rotina de dentro o tanta de vezes que a frequencia desejada cabe dentro da duracao
    digitalWrite(pinoBuz,HIGH);
    delayMicroseconds(periodo*500); //Metade do periodo em ms
    digitalWrite(pinoBuz, LOW);
    delayMicroseconds(periodo*500);
  }
}

void debug(float cmMsec) {
  Serial.print("Contador: ");
  Serial.print(count);
  Serial.print(" | ");
  Serial.print(" Tipo: ");
  Serial.print(a_tipo);
  Serial.print(" | ");
  Serial.print("Distancia: ");
  Serial.print(cmMsec);
  Serial.print(" | ");
  Serial.print("\n");
}

void setup()
{
  Serial.begin(9600);
  pinMode(pinoBuz, OUTPUT);
  pinMode(pinoBot, INPUT_PULLUP);
  
  for(int i = 0; i < qtdLED; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
}
 
void loop()
{

  if(!digitalRead(pinoBot)) {
    delay(120);
    ligado = !ligado;
  }

  if(ligado) {

    Ultrasonic ultrasonic(trig, echo);
    float cmMsec = ultrasonic.read();

    if(cmMsec >= 30 + car_offset && cmMsec < 40 + car_offset) {

      if(a_tipo != 0) {
        a_tipo = 0;
        count = 0;
        for (int i = qtdLED; i > qtdLED - 4; i--) {
          digitalWrite(LEDs[i], LOW);
        }
      }
      else {
        if(count < 20 * nivel1) {
          tom(10, 330, 100);
          for(int i = 0; i < qtdLED - 4; i++) {
            digitalWrite(LEDs[i], HIGH);
          }
          delay(350 + secDebug);
          count++;

          debug(cmMsec);
        }
      }
    }

    if(cmMsec >= 20 + car_offset && cmMsec < 30 + car_offset) {

      if(a_tipo != 1) {
        a_tipo = 1;
        count = 0;
        for(int i = qtdLED; i > qtdLED - 3; i--) {
          digitalWrite(LEDs[i], LOW);
        }
      }
      else {
          if(count < 20 * nivel1) {
            tom(10, 330, 100);
            for(int i = 0; i < qtdLED - 3; i++) {
            digitalWrite(LEDs[i], HIGH);
            }
            delay(250 + secDebug);
            count++;

            debug(cmMsec);
          }
      }
    }
    if(cmMsec >= 15 + car_offset && cmMsec < 20 + car_offset) {

      if(a_tipo != 2) {
        a_tipo = 2;
        count = 0;
        for(int i = qtdLED; i > qtdLED - 2; i--) {
          digitalWrite(LEDs[i], LOW);
        }
      }
      else {
        if(count < 20 * nivel2) {
          tom(10, 330, 100);
          for(int i = 0; i < qtdLED - 2; i++) {
            digitalWrite(LEDs[i], HIGH);
          }
          delay(100 + secDebug);
          count++;

          debug(cmMsec);
        }
      }
    }
    if(cmMsec < 15 + car_offset && cmMsec > 6 + car_offset) {
      if(a_tipo != 3) {
        a_tipo = 3;
        count = 0;
        for(int i = qtdLED; i > qtdLED - 1; i--) {
          digitalWrite(LEDs[i], LOW);
        }
      }
      else if(count < 20 * nivel1){
        tom(10, 330, 100);
        for(int i = 0; i < qtdLED - 1; i++) {
          digitalWrite(LEDs[i], HIGH);
        }
        delay(50 + secDebug);
        count++;

        debug(cmMsec);
      }
    }
    if(cmMsec <= 6 + car_offset) {
      if(a_tipo != 4) {
        a_tipo = 4;
        count = 0;
        }
      }
      else if(count < 20 * nivel2){
        tom(10, 330, 100);
        for(int i = 0; i < qtdLED; i++) {
          digitalWrite(LEDs[i], HIGH);
        }
        delay(secDebug);
        count++;

        debug(cmMsec);
      }   
  }

}