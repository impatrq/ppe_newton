#ifndef DHT_H
#define DHT_H

#include <stdbool.h>
#include "pico/stdlib.h"

// Estructura para almacenar lecturas
typedef struct
{
    float humidity;
    float temp_celsius;
    bool valid;
} dht_reading_t;

// Inicialización
void dht_init(uint pin);

// Lectura
dht_reading_t read_from_dht(void);

#endif
