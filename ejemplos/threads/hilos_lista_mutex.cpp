/*

Proteger las inserciones en una lista mediante mutex

*/

#include <thread>
#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

std::list<int> lista = {1,2,3,5,6,7,8,4,9,10};
std::mutex miMutex;


void addToList(int val){
	std::lock_guard<std::mutex> guard(miMutex);
	lista.push_back(val);
}


bool listContains(int val){
	std::lock_guard<std::mutex> guard(miMutex);
	return std::find(lista.begin(), lista.end(), val) != lista.end();
}

void printLista(){
	std::lock_guard<std::mutex> guard(miMutex);
	for (auto &i : lista)
		std::cout << i << " ";
	std::cout << std::endl;
}

void insertar(){
	// El hilo llama sucesivas veces a la funcion de insertar...
	int valor;

	for (int i = 0 ; i < 10 ; i++){
		valor = (i+1)*10;		
		addToList(valor);
		std::cout << "Insertar: " << valor << std::endl;	
	}
	
}

void buscar(){
	// Busca numeros aleatorios entre 0 y 100.


}

int main(){
	
	printLista();
	

	// Definir un hilo que se encarge de añadir elementos a la lista y otro de buscar:
	std::thread hiloAdd(insertar);
	std::thread hiloLook(buscar);

 	hiloAdd.join();

	
}
