# Desplegar una war en tomcat:

# La imagen base: servidor tomcat
FROM tomcat

# Como directorio de trabajo selecciona la carpeta de publicacion de tomcat
WORKDIR /usr/local/tomcat/webapps

# Copia el archivo war en el contenedor:
COPY aplicacion1.war .

# Exponer el puerto:
EXPOSE 8080