/*  usrport RTU Slave example
 *  usr ip:           192.168.0.7 (default)
        port:         23 (default)
        mode:         tcp sever modbus tcp
        usr serial :  115200 8n1 (default)
 */
#include <MULTI.h>
bool coils[10];
bool discreteInputs[10];
uint16_t holdingRegisters[10];
uint16_t inputRegisters[10];

void setup() {

  usrRTUSlave.configureCoils(coils, 10);                       // bool array of coil values, number of coils
  usrRTUSlave.configureDiscreteInputs(discreteInputs, 10);     // bool array of discrete input values, number of discrete inputs
  usrRTUSlave.configureHoldingRegisters(holdingRegisters, 10); // unsigned 16 bit integer array of holding register values, number of holding registers
  usrRTUSlave.configureInputRegisters(inputRegisters, 10);     // unsigned 16 bit integer array of input register values, number of input registers

  usrRTUSlave.begin(1, 115200);
}

void loop() {
  static uint8_t indexOUT = 0;
  static uint64_t _stRtn1 = millis();
  if (millis() - _stRtn1 > 100) {
    for (uint8_t i = 0; i < 5; i++) {
      if(i != indexOUT) {
        coils[i] = 0;
        discreteInputs[i] = 0;
        holdingRegisters[i] = 0;
        inputRegisters[i] = 0;
      }
      else {
        coils[i] = 1;
        discreteInputs[i] = 1;
        holdingRegisters[i] = 1;
        inputRegisters[i] = 1;
        }
    }
    
    _stRtn1 = millis();
    indexOUT < 5 ? indexOUT++ : indexOUT = 0;
  }
  usrRTUSlave.poll();
}