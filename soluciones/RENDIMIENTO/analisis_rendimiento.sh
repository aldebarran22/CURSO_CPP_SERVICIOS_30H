#!/bin/bash

# Nombre del ejecutable
EXEC="./microservicio"

# Verifica que el ejecutable existe
if [ ! -f "$EXEC" ]; then
    echo "Ejecutable no encontrado: $EXEC"
    exit 1
fi

echo "Iniciando análisis con Valgrind..."
valgrind --leak-check=full --log-file=valgrind.log $EXEC &
PID=$!
sleep 5
kill $PID
echo "Valgrind completado. Revisa valgrind.log"

echo "Compilando con soporte para gprof..."
g++ -pg -O2 main.cpp -o microservicio_gprof
echo "Ejecutando microservicio con gprof..."
./microservicio_gprof
echo "Generando informe gprof..."
gprof microservicio_gprof gmon.out > gprof_report.txt
echo "Informe gprof generado: gprof_report.txt"

echo "Ejecutando perf..."
perf record -F 99 -g $EXEC
perf report > perf_report.txt
echo "Informe perf generado: perf_report.txt"

echo "Todos los análisis completados."
