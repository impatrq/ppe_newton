#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "hw_config.h"
#include "f_util.h"
#include "ff.h"
#include "lib/ds1302.h"
#include "lib/max6675.h"
#include "lib/acs712.h"
#include "lib/dht.h"

acs712_t current_sensor;
int _dat_direction;

int _pin_clk;
int _pin_dat;
int _pin_rst;

#define DHT_PIN 15
#define MAX_TIMINGS 85

#define PIN_GPIO_CLK 18
#define PIN_GPIO_DAT 17
#define PIN_GPIO_RST 16

int main()
{

    _pin_rst = PIN_GPIO_RST;
    _pin_clk = PIN_GPIO_CLK;
    _pin_dat = PIN_GPIO_DAT;
    _dat_direction = 0; // Initialize direction

    stdio_init_all();
    ds1302init(PIN_GPIO_RST, PIN_GPIO_CLK, PIN_GPIO_DAT);
    dht_init(DHT_PIN);
    acs712_init(&current_sensor, 26, 66.0, 3.24); // sensibilidad: 66 mV/A (ejemplo: ACS712-20A), tener en cuenta estabilidad de Vref y ruido.
    acs712_calibrate(&current_sensor, 100);
    float adc;
    float current;
    float temp;

    for (int k = 0; k < 100; k++)
    {
        printf("Inicializando... %d/100\n", k);
        sleep_ms(100);
    }

    writeProtect(0); // disable write protection
    DateTime now;
    ds1302getDateTime(&now);
    sleep_ms(2000);

    // test bulk RAM ops - write ASCII (from msparks)
    uint8_t ram[kRamSize];
    readRamBulk(ram, kRamSize);
    printf("%s\n", (const char *)ram);

    // --- Inicialización de la SD ---
    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);
    if (FR_OK != fr)
    {
        panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    // Abrir archivo para append
    FIL fil;
    const char *const filename = "dht_log.txt";
    fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr)
    {
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    }

    // Loop de lectura
    while (1)
    {
        current = acs712_read_current(&current_sensor);
        adc = adc_read();
        temp = max6675_read();
        ds1302getDateTime(&now);
        // printf("DateTime second %d\n", now.second); // OK 0-59
        char *dow = "Noneday";
        switch (now.dow)
        {
        case DOW_MON:
            dow = "Lunes";
            break;
        case DOW_TUE:
            dow = "Martes";
            break;
        case DOW_WED:
            dow = "Miércoles";
            break;
        case DOW_THU:
            dow = "Jueves";
            break;
        case DOW_FRI:
            dow = "Viernes";
            break;
        case DOW_SAT:
            dow = "Sábado";
            break;
        case DOW_SUN:
            dow = "Domingo";
            break;
        default:
            break;
        }
        printf("%02d/%02d/20%d %02d:%02d:%02d %s, Temperatura=%.2f, Corriente=%.2f, ADC=%.2f\n", now.month, now.day, now.year,
               now.hour, now.minute, now.second,
               dow, temp, current, adc);

        dht_reading_t reading = read_from_dht();
        if (reading.valid)
        {
            float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
            printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
                   reading.humidity, reading.temp_celsius, fahrenheit);

            // Guardar en la SD
            if (f_printf(&fil,
                         "%02d/%02d/20%d %02d:%02d:%02d - H=%.1f%%, T=%.1fC (%.1fF), I=%.2f A\n",
                         now.day, now.month, now.year,
                         now.hour, now.minute, now.second,
                         reading.humidity, temp, fahrenheit, current) < 0)

            {
                printf("Error escribiendo en SD\n");
            }

            // Asegurar escritura inmediata
            f_sync(&fil);
        }
        else
        {
            printf("Bad data\n");
        }

        sleep_ms(1000);
    }

    // Nunca se llega acá
    f_close(&fil);
    f_unmount("");
    return 0;
}
