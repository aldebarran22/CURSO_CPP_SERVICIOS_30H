# Utilizar plantilla ligera:
FROM python:3.9-slim

# Establecer directorio de trabajo:
WORKDIR /app

# Copiar fichero de requisitos:
COPY requirements.txt .

# Lanzar un comando:
RUN pip install --no-cache-dir -r requirements.txt

COPY app.py .

EXPOSE 5000

CMD ["python", "app.py"]
