/*

Hilos en CPP 11

4 hilos:

Este programa sirve para comprobar la necesidad del uso de mutex para recursos compartidos entre 2 o mas hilos.

Tenemos 4 hilos,

Dos hilos suman y restan 1 a un contador compartido sin utilizar mecanismos de sincronizacion.
Y los otros dos hacen lo mismo pero en este caso utilizando un mutex para proteger el acceso
al contador protegido.


*/

#include <iostream>
#include <thread>
#include <mutex>

#define ITERACIONES 1000000

int contador1 = 0;
int contador2 = 0;

std::mutex miMutex;


void sumador1(){
	for (int i = 0 ; i < ITERACIONES  ; i++)
		contador1++;
}

void restador1(){
	for (int i = 0 ; i < ITERACIONES  ; i++)
		contador1--;
}


void sumador_mutex(){
	for (int i = 0 ; i < ITERACIONES  ; i++){
		// Se aconseja NO utilizar lock y unlock porque si se nos olvida hacer unlock, estariamos dejando bloqueado el recurso
		std::lock_guard<std::mutex> guard(miMutex);
		contador2++;
	}
}

void restador_mutex(){
	for (int i = 0 ; i < ITERACIONES  ; i++){
		// Esta es la otra opcion de bloquear y desbloquear el mutex, es mejor la de la funcion anterior
		miMutex.lock();
		contador2--;
		miMutex.unlock();
	}
}



int main(){

	std::thread h1(sumador1);
	std::thread h2(restador1);

	std::thread h3(sumador_mutex);
	std::thread h4(restador_mutex);

	h1.join();	
	h2.join();
	h3.join();
	h4.join();

	// Imprimir los resultados:
	printf("\nContador1 sin proteccion: %d", contador1);
	printf("\nContador2 con proteccion: %d", contador2);	
	puts("");
}
