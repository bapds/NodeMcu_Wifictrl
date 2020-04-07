#include <Arduino.h>
int btn1_pin = 9;
int btn2_pin = 10;
int btn1 = 0;
int btn2 = 0;

int led1 = 0;
int led2 = 1;
int led3 = 2;
int led4 = 3;
int led5 = 4;
int led6 = 5;
int led7 = 12;
int led8 = 13;
int led9 = 14;
int led10 = 15;
int led11 = 16;
//int led12 = 33;

int tempo = 1000;

// the setup routine runs once when you press reset:
void setup() {               
  pinMode(btn1_pin, INPUT);  
  pinMode(btn2_pin, INPUT);  
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);

}

void piscar(int i) {
    digitalWrite(i, HIGH);
    delay(tempo);
    digitalWrite(i, LOW);
    delay(tempo);
}

void ligar(int i) {
    digitalWrite(i, HIGH);
    delay(tempo);
}

void desligar(int i) {
    digitalWrite(i, LOW);
    delay(tempo);
}

void func1(bool cmd){
  if (cmd == true){
    for (int i=0; i <= 5; i++){
      ligar(i);
    }
    for (int i=12; i <= 16; i++){
      ligar(i);
    }

    for (int j=16; j >= 12; j--){
      desligar(j);
    } 
    for (int j=5; j >= 0; j--){
      desligar(j);
    } 
  }
}

void func2(bool cmd){
  if (cmd == true){

    for (int j=16; j >= 12; j--){
      desligar(j);
    } 
    for (int j=5; j >= 0; j--){
      desligar(j);
    } 
    cmd = false;
  }
}

void func3(bool cmd){
  if(cmd==true){

    for (int k=0; k <= 5; k++){
      piscar(k);
    } 
    for (int k=12; k <= 16; k++){
      piscar(k);
    } 
  }
}
// the loop routine runs over and over again forever:
void loop() {  

  btn1 = digitalRead(btn1_pin);   // read the input pin
  btn2 = digitalRead(btn2_pin);   // read the input pin

  if (true){
    func1(true);
    func2(false);
    func3(false);
  }
  else{
    func1(false);
  }

  if (true){  
    func2(true);
    func1(false);
    func3(false);
  }
  else{
    func2(false);    
  }

  if (true){
    func3(true);
    func1(false);
    func2(false);
   } 
  else{
    func3(false);
  }
}