/*  ADS8688 example
 *  R0:  Input range to -2.5/+2.5         Vref   +/- 10.24V
 *  R1:  Input range to -1.25/+1.25       Vref   +/-  5.12V
 *  R2:  Input range to -0.625/+0.625     Vref   +/-  2.56V
 *  R3:  Input range to -0.3125/+0.3125   Vref   +/-  1.28V
 *  R4:  Input range to -0.15625/+0.15625 Vref   +/-  0.64V
 *  R5:  Input range to +2.5              Vref   10.24V
 *  R6:  Input range to +1.25             Vref    5.12V
 *  R7:  Input range to +0.625            Vref    2.56V
 *  R8:  Input range to +0.3125           Vref    1.28V
 */

#include <MULTI.h>
ADS8688 AI;
uint16_t adc[8];
uint8_t inputType[8] = {R6, R6, R6, R6, R6, R6, R6, R6};

void setup() {
    Serial.begin(9600);
    AI.begin(inputType);
}

void loop() {
    AI.readAll(adc);
    for(uint8_t i = 0; i<8; i++){
      Serial.printf("ch%d: %f ", i, AI.toVoltage(adc[i]));
    }
    Serial.println();
    delay(500);
}