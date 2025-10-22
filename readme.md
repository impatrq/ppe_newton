# Visualización de Datos del Datalogger

Este apartado del proyecto corresponde a la rama **Grafico-De-Datos**, donde se incluye un script en Python para graficar los datos registrados por el datalogger.

## Contenido

- **Script/**  
  Carpeta que contiene:
  - `plot_dht.py`: programa en Python que lee el archivo de registro y genera un gráfico de las mediciones.  
  - `dht_log.txt`: archivo de ejemplo con datos reales tomados por el datalogger.

## Como ejecutar el programa

- Primero se debe descargar la carpeta del script que contiene el programa en Python, `plot_dht.py` y se abre está carpeta dentro de Visual Studio Code
- Se debe verificar tener instalado Python para poder ejecutar el archivo
  El siguiente paso es para verificar tener instalado Python, si ya está instalado se puede omitir:
  - Escribir en la terminal de Visual Studio Code
    ```bash
    python --version
  - Si está instalado dirá que versión de Python está instalado

- Luego de instalar Python se deben instalar las librerias necesarias
  - Para ello se escribirá en la terminal de Visual Studio Code
    ```bash
    pip install pandas
  - También se debe instalar la libreria de matplotlib
    ```bash
    pip install matplotlib

Con las librerias necesarias instaladas, al ejecutar el programa se mostrará un gráfico con los datos que se proporcionen en el archivo `dht_log.txt`


