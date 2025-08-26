#ifndef MAX6675_H
#define MAX6675_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

// Pines por defecto (puedes cambiarlos desde main si querés)
#define MAX6675_PIN_MISO 12
#define MAX6675_PIN_CS 13
#define MAX6675_PIN_SCK 14

// Inicializa el MAX6675 con SPI
void max6675_init(spi_inst_t *spi, uint miso_pin, uint sck_pin, uint cs_pin);

// Lee la temperatura en °C
float max6675_read(void);

#endif
