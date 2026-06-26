## Imagen basada en Ubuntu
FROM ubuntu

# Actualizar el sistema:
RUN apt-get update

# Establece Zona horaria con una variable:
ENV TZ=Europe/Madrid

# Crear un fichero en el contenedor: /etc/timezone
RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

# instalar nginx
RUN apt-get install -y nginx

# Generar un fichero y copiar a la carpeta de publicación del nginx
RUN echo 'Prueba del nginx en un POD'  > /var/www/html/index.html

# Arrancar nginx:
ENTRYPOINT [ "/usr/sbin/nginx", "-g", "daemon off;" ]

# Exponer el puerto:
EXPOSE 80

## Pasos en Docker: 
# Crear la imagen: docker build -t mi_ubuntu_nginx .
# Etiquetar la imagen: docker tag mi_ubuntu_nginx usuario_DH/mi_ubuntu_nginx:v1
# docker login
# docker push usuario_DH/mi_ubuntu_nginx:v1

## Pasos con kubectl:
# Crear el fichero YAML para el POD
# Crear el POD con: kubectl apply -f fichero.yaml
# Para ver si está corriendo: kubectl get pod
# Para comprobarlo: kubectl port-forwading 7500:80
# En el navegador: http://localhost:7500


