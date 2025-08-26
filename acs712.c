#include "lib/acs712.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"

// Inicializar el sensor
void acs712_init(acs712_t *sensor, uint adc_pin, float sensitivity, float vref)
{
    sensor->adc_pin = adc_pin;
    sensor->sensitivity = sensitivity;
    sensor->vref = vref;
    sensor->resolution = (1 << 12);   // 12 bits
    sensor->zero_offset = vref / 2.0; // valor teórico inicial

    adc_init();
    adc_gpio_init(sensor->adc_pin);
    adc_select_input(sensor->adc_pin - 26);
}

// Calibrar en reposo (sin corriente)
void acs712_calibrate(acs712_t *sensor, int samples)
{
    uint32_t sum = 0;
    for (int i = 0; i < samples; i++)
    {
        sum += adc_read();
        sleep_ms(2);
    }
    uint16_t avg_raw = sum / samples;
    sensor->zero_offset = (avg_raw * sensor->vref) / (sensor->resolution - 1);
}

// Leer corriente en amperios
float acs712_read_current(acs712_t *sensor)
{
    uint16_t raw = adc_read();
    float voltage = (raw * sensor->vref) / (sensor->resolution - 1);

    // Usar offset calibrado
    float current = (voltage - sensor->zero_offset) / (sensor->sensitivity / 1000.0);
    return current;
}
