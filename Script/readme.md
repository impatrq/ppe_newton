# Script de Visualización de Datos

Este directorio contiene el script en Python que permite leer y graficar los datos registrados por el datalogger
Incluye también un registro de ejemplo real tomada de un muestreo con la data logger, este se toma como referencia
para verificar el funcionamiento del script.

## Contenido

- **plot_datalogger.py** → Programa en Python.  
  Lee un archivo de texto con los datos generados por el datalogger y muestra un gráfico con las mediciones.
  Crea también un excel para poder visualizar los datos de una manera más intuitiva

- **registro_ejemplo.txt** → Archivo de ejemplo con mediciones reales tomadas por el datalogger.  
  Se utiliza para probar el funcionamiento del script sin necesidad de un nuevo registro.

## Requisitos

Antes de ejecutar el programa, asegurate de tener instaladas las siguientes librerías:
(La instalación se explica más a detalle en la sección principal del repositorio)
```bash
pip install pandas
pip install matplotlib


