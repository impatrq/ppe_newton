import re
import os
import pandas as pd
import matplotlib.pyplot as plt

# Función para leer el archivo
def parse_log(path):
    data = []
    with open(path, "r") as f:
        for line in f:
            try:
                timestamp, temp, hum = line.strip().split(",")
                data.append((timestamp, float(temp), float(hum)))
            except:
                pass
    return pd.DataFrame(data, columns=["Timestamp", "Temp", "Hum"])

# Ruta al archivo (Verificar si el programa no lo encuentra)
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, "dht_log.txt")


# Expresión para leer las líneas del txt
pattern = re.compile(
    r'(?P<date>\d{2}/\d{2}/\d{4}) (?P<time>\d{2}:\d{2}:\d{2}) - H=(?P<H>[\d.]+)%, T=(?P<Tc>[\d.]+)C.*?I=(?P<I>[-\d.]+) A'
)

def parse_log(path):
    rows = []
    with open(path, "r") as f:
        for line in f:
            m = pattern.search(line)
            if m:
                try:
                    ts = pd.to_datetime(m["date"] + " " + m["time"], dayfirst=True)
                    # Se asegura de que la fecha y hora sean válidas (ignora las lineas, porque sino no andaría el script)
                except ValueError:
                    print(f"Línea con fecha/hora inválida ignorada: {line.strip()}")
                    continue
                
                try:
                    H = float(m["H"])
                    Tc = float(m["Tc"])
                    I = float(m["I"]) if m["I"] else None
                    # Idem; se asegura de que los valores numéricos sean válidos
                except ValueError:
                    print(f"Línea con valor numérico inválido ignorada: {line.strip()}")
                    continue
                
                if not (0 <= H <= 100):
                    continue
                if not (-40 <= Tc <= 80):
                    continue
                rows.append([ts, H, Tc, I])
    return pd.DataFrame(rows, columns=["timestamp", "humidity", "tempC", "current"])

# Leer y parsear el archivo
df = parse_log("dht_log.txt") # Lee el archivo de tu SD
print(df.head()) # Verifica que se haya leído correctamente

# Guardar como CSV limpio (Para abrir en Excel)
df.to_csv("dht_log_limpio.csv", index=False)

# Graficar con eje secundario para la corriente
plt.figure(figsize=(10,6))

# Eje principal a la izquierda: humedad y temperatura
ax1 = plt.gca()
line1, = ax1.plot(df["timestamp"], df["humidity"], label="Humedad (%)", color="blue")
line2, = ax1.plot(df["timestamp"], df["tempC"], label="Temp (°C)", color="red")
ax1.set_xlabel("Tiempo")
ax1.set_ylabel("Humedad / Temp")
ax1.legend(handles=[line1, line2], loc="upper left")

# Cuadrícula suave en el eje principal
ax1.grid(True, which='both', linestyle='--', linewidth=0.9, alpha=0.9)

# Eje secundario: corriente
if df["current"].notna().any():
    ax2 = ax1.twinx()
    line3, = ax2.plot(df["timestamp"], df["current"], label="Corriente (A)", color="green")
    ax2.set_ylabel("Corriente (A)")
    ax2.legend(handles=[line3], loc="upper right")

plt.tight_layout()
# Mostrar la gráfica
plt.show()

