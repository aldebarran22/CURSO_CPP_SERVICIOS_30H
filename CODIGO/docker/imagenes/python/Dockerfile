# Desplegar un servicio de Python

FROM python:3.9-slim

# Establecer el directorio de trabajo:
WORKDIR /app

COPY requisitos.txt .

# Lanzar un comando para instalar las librerias (en requisitos)
RUN pip install --no-cache-dir -r requisitos.txt

COPY app.py .

EXPOSE 5000

CMD ["python", "app.py"]
