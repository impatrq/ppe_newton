#include "lib/max6675.h"

static spi_inst_t *spi_used;
static uint pin_cs;

void max6675_init(spi_inst_t *spi, uint miso_pin, uint sck_pin, uint cs_pin)
{
    spi_used = spi;
    pin_cs = cs_pin;

    spi_init(spi_used, 1000 * 1000); // 1 MHz (MAX6675 hasta 4.3 MHz)
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);

    gpio_init(pin_cs);
    gpio_set_dir(pin_cs, GPIO_OUT);
    gpio_put(pin_cs, 1); // CS deseleccionado
}

float max6675_read(void)
{
    uint8_t buffer[2];
    uint16_t value;

    gpio_put(pin_cs, 0);
    sleep_us(10);

    spi_read_blocking(spi_used, 0x00, buffer, 2);
    gpio_put(pin_cs, 1);

    value = ((uint16_t)buffer[0] << 8) | buffer[1];

    if (value & 0x4)
    {
        // bit D2 = 1 → no hay termocupla conectada
        return -1000.0f;
    }

    value >>= 3; // bits D[15:3]
    return value * 0.25f;
}
