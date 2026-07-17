# Utilizar una imagen ligera con el runtime de python
FROM python:3.9-slim

# Establecer directorio de trabajo:
WORKDIR /app

# Copiar el fichero de requisitos:
COPY requisitos.txt .

# Lanzar un comando de instalacion:
RUN pip install --no-cache-dir -r requisitos.txt

COPY app.py .

EXPOSE 5000

CMD ["python", "app.py"]
