/*  rs485port RTU Master example
 */
#include <MULTI.h>
bool coils[20];
bool discreteInputs[20];
uint16_t holdingRegisters[20];
uint16_t inputRegisters[20];

void setup() {
  rs485RTUMaster.begin(19200);
}

void loop() {
  static uint64_t _stRtn1 = millis();
  static uint16_t i = 0;
  if (millis() - _stRtn1 > 100) {
      i++;
      holdingRegisters[0] = 0 + i;
      holdingRegisters[1] = 1 + i;
      holdingRegisters[2] = 2 + i;
      holdingRegisters[3] = 3 + i;
      holdingRegisters[4] = 4 + i;
      holdingRegisters[5] = 5 + i;
      _stRtn1 = millis();
  }
  rs485RTUMaster.writeMultipleHoldingRegisters(1, 0, holdingRegisters, 5);
}