# Crear una imagen del servidor nginx con una pagina personalizada:

FROM ubuntu:22.04

# Instalar el servidor nginx:
RUN apt-get update && apt-get install -y nginx

# Copiar la pagina index.html a la carpeta de publicacion de nginx
COPY index.html /var/www/html/index.html

# Exponer un puerto:
EXPOSE 80

# Lanzar un comando para arrancar el servidor nginx
CMD ["nginx", "-g", "daemon off"]
