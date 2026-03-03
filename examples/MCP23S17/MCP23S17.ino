/*  MCP23S17 example
 *  0:  Output
 *  1:  Input
 *  2:  Input
 */

#include <MULTI.h>
MCP23S17 Bank1(0);
MCP23S17 Bank2(1);
MCP23S17 Bank3(2);
uint8_t indexOUT = 0;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(mcp23s17_rst, OUTPUT);
  digitalWrite(mcp23s17_rst, HIGH);
  delay(1000);
  Bank1.begin();
  Bank1.enableHardwareAddress();
  Bank2.begin();
  Bank2.enableHardwareAddress();
  Bank3.begin();
  Bank2.enableHardwareAddress();

  for (uint8_t i = 0; i < 16; i++) {
    Bank1.pinMode(i, OUTPUT);
    Bank2.pinMode(i, INPUT_PULLUP);
    Bank3.pinMode(i, INPUT_PULLUP);
    delay(100);
  }
}


void loop() {
  //DI
  static uint64_t _stRtn0 = millis();
  if (millis() - _stRtn0 > 500) {
    Serial.print("DI: 0x");

    for (uint8_t i = 0; i < 16; i++) {
      Serial.print(Bank2.digitalRead(i));
      delay(1);
    }

    Serial.print(" 0x");

    for (uint8_t i = 0; i < 16; i++) {
      Serial.print(Bank3.digitalRead(i));
      delay(1);
    }

    Serial.println();
    _stRtn0 = millis();
  }

  //DO
  static uint64_t _stRtn1 = millis();
  if (millis() - _stRtn1 > 100) {
    for (uint8_t i = 0; i < 16; i++) {
      if(i != indexOUT) Bank1.digitalWrite(i, LOW);
      else {
        Bank1.digitalWrite(i, HIGH); 
        }
    }
    
    _stRtn1 = millis();
    indexOUT < 16 ? indexOUT++ : indexOUT = 0;
  }
}