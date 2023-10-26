/*
GND до GND на Arduino
VCC до живлення на Arduino
U/D до цифрового піна (наприклад, 8)
INC до цифрового піна (наприклад, 9)
CS до цифрового піна (наприклад, 10)

реле In1, підключений до цифрового реле реле 12

резистор 1 до піна А1
резистор 2 до піна А2 
*/


#include <Arduino.h>
#include <EncButton.h>

#include "X9C103S_digipot.h"
DigiPot pot1(10, 8,9);
EncButton eb(2, 3, 4);
const int relayControlPin = 12; // Пін D3 для керування реле

int potentiometer1Value = 0;
int potentiometer2Value = 0;
int potentiometer3Value = 0;
int Relay = 12; // Вказуємо, що виведення реле In1, підключений до цифрового реле реле 12

const int x9c103sUdPin = 8;  // Пін U/D підключений до X9C103S
const int x9c103sIncPin = 9; // Пін INC підключений до X9C103S
const int x9c103sCsPin = 10; // Пін CS підключений до X9C103S

void setup() {
  pot1.reset();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);  
  pinMode(x9c103sUdPin, OUTPUT);
  pinMode(x9c103sIncPin, OUTPUT);
  pinMode(x9c103sCsPin, OUTPUT);
  digitalWrite(6, LOW);  // Вимкнути перший світлодіод
  digitalWrite(7, HIGH); // Увімкнути другий світлодіод
  pinMode(12, OUTPUT);  
   
  Serial.begin(115200);
}
/*
void setX9C103SValue(int value) {
  // Обмежте значення від 0 до 1023
  value = constrain(value, 0, 1023);
  // Виконайте лінійне відображення значення на діапазон від 0 до 10,000
  int mappedValue = map(value, 0, 1023, 0, 99);
  digitalWrite(x9c103sUdPin, HIGH);  // Установіть U/D в HIGH для збільшення значення
  for (int i = 0; i < mappedValue; i++) {
    digitalWrite(x9c103sIncPin, HIGH);
    digitalWrite(x9c103sIncPin, LOW);
  }
  digitalWrite(x9c103sCsPin, HIGH);  // Завершіть зміну значення
}
*/

void loop() {

  
  eb.tick();
  potentiometer1Value = analogRead(A1);
  potentiometer2Value = analogRead(A2);
  potentiometer3Value = analogRead(A3);
// состояния
     //Serial.println(eb.pressing());
    // Serial.println(eb.holding());
     Serial.println(eb.busy());
     //Serial.println(eb.waiting());
  
  if (eb.press()) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
 
    pot1.write(map(analogRead(A1), 0, 1023, 0, 99));
    digitalWrite(relayControlPin, HIGH);
    Serial.println("456");
    Serial.println("Button pressed");

   //setX9C103SValue(potentiometer2Value); // Встановити значення X9C103S при натисканні кнопки
  }
  if (eb.step()) {
    Serial.println("step");
   // pot1.write(map(analogRead(A2), 0, 1023, 0, 99));
  }
   if (eb.releaseStep()) {
    //pot1.write(map(analogRead(A1), 0, 1023, 0, 99));
     Serial.println("release step");
   }
   if (eb.busy()){
         pot1.write(map(analogRead(A2), 0, 1023, 0, 99));
 digitalWrite(12, HIGH); // Выключаем реле
            Serial.print("potentiometer оне ");
      }
  else {
              pot1.write(map(analogRead(A1), 0, 1023, 0, 99));
               digitalWrite(12, LOW); // Выключаем реле

                          Serial.print("potentiometer Two__ ");

            }
  if (eb.release()) {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    pot1.write(map(analogRead(A1), 0, 1023, 0, 99));
    Serial.print("potentiometer оне ");
    Serial.println(potentiometer1Value);
    Serial.print("potentiometer тву");
    Serial.println(potentiometer2Value);
    Serial.print("potentiometer срі");
    Serial.println(potentiometer3Value);
    Serial.println("Button released");
      digitalWrite(relayControlPin, LOW);
    //setX9C103SValue(potentiometer1Value); // Встановити значення X9C103S при відпусканні кнопки
  }
   
/*
  if (eb.hasClicks(3)) {
    Serial.println("has 3 clicks");
    Serial.print("Number of clicks: ");
    Serial.println(eb.getClicks());*/
  }

