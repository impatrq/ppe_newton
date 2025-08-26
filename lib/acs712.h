#ifndef ACS712_H
#define ACS712_H

#include "pico/stdlib.h"

typedef struct
{
    uint adc_pin;
    float sensitivity;   // mV por A (ej: 185 para ACS712-5A)
    float vref;          // Voltaje de referencia (normalmente 3.3V)
    uint16_t resolution; // Resolución ADC (4096 para 12 bits)
    float zero_offset;   // Offset calibrado en voltios
} acs712_t;

void acs712_init(acs712_t *sensor, uint adc_pin, float sensitivity, float vref);
void acs712_calibrate(acs712_t *sensor, int samples);
float acs712_read_current(acs712_t *sensor);

#endif
