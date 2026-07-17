# Crear una imagen a partir de ubuntu, instalar el servidor nginx y sustituir la pagina de inicio
FROM ubuntu:22.04

# Instalar el servidor nginx
RUN apt-get update && apt-get install -y nginx

# Copiar el fichero index.html para sustituir la pagina de inicio del servidor
COPY index.html /var/www/html/index.html

# Exponer el puerto
EXPOSE 80

# Lanzar un comando para arrancar el servidor nginx
CMD ["nginx", "-g", "daemon off;"]
