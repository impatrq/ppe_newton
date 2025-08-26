# Datalogger 

Proyecto de registro de datos usando **Raspberry Pi Pico**, sensores de temperatura, humedad, corriente y un RTC externo.  
Los datos se guardan en una **tarjeta SD** para análisis posterior.

---

## Hardware usado

| Sensor / Componente | Pin | Descripción |
|-------------------|----------|-------------|
| DHT22 (temperatura y humedad) | GP15 | Lectura digital de temperatura y humedad |
| MAX6675 (termopar K) | GP16 (CS), GP17 (MISO), GP18 (SCK) | Lectura de temperatura por SPI |
| ACS712 (sensor de corriente) | GP26 (ADC0) | Medición de corriente en amperios |
| DS1302 (RTC) | GP16 (RST), GP17 (CLK), GP18 (DAT) | Reloj en tiempo real para timestamps |
| SPI Tarjeta SD| GPI2(MISO), GP3(MOSI), GP4(SCK), GP7(CS) | Registro de datos en la tarjeta SD |


---

## Librerías

- **DHT**: Lectura de temperatura y humedad.
- **MAX6675**: Lectura de termopar tipo K.
- **ACS712**: Lectura de corriente con sensor Hall.
- **DS1302**: Reloj en tiempo real.
- **FatFS**: Sistema de archivos para la tarjeta SD.

---

## Compilación

1. Instalar el SDK de Raspberry Pi Pico.
2. Ejecutar CMake desde la carpeta raíz:
```bash
mkdir build
cd build
cmake ..
make
