#include "lib/dht.h"
#include "hardware/gpio.h"

static uint DHT_PIN;
const uint MAX_TIMINGS = 85;

void dht_init(uint pin)
{
    DHT_PIN = pin;
    gpio_init(DHT_PIN);
}

// Función de lectura
dht_reading_t read_from_dht(void)
{
    int data[5] = {0, 0, 0, 0, 0};
    uint last = 1;
    uint j = 0;
    dht_reading_t result = {0.0f, 0.0f, false};

    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0);
    busy_wait_ms(20);
    gpio_put(DHT_PIN, 1);
    busy_wait_us(40);
    gpio_set_dir(DHT_PIN, GPIO_IN);

    for (uint i = 0; i < MAX_TIMINGS; i++)
    {
        uint count = 0;
        while (gpio_get(DHT_PIN) == last)
        {
            count++;
            busy_wait_us(1);
            if (count == 255)
                break;
        }
        last = gpio_get(DHT_PIN);

        if (count == 255)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            data[j / 8] <<= 1;
            if (count > 40)
                data[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        result.humidity = data[0];
        result.temp_celsius = data[2];
        result.valid = true;
    }

    return result;
}
