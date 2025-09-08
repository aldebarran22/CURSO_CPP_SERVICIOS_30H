/*

Tareas asincronas y futuros

*/


#include <future>
#include <iostream>


int tarea(int ini, int fin){
	int sum = 0;

	for (int i = ini ; i <= fin ; i++){
		//std::cout << "Tarea: " << i << std::endl;
		sum += i;
	}
	
}

void otra_tarea(){

	int i=10000000;
	
	std::cout << "Se inicia otra_tarea() " << std::endl;
	while (i){
		i--;
	}
	std::cout << "Se finaliza otra_tarea() " << std::endl;
}

int main(){
	// Esta llamada no es bloqueante. Se va calculando mientras se lanza otra_tarea.
	std::future<int> resul = std::async(tarea, 1,100);
	otra_tarea();

	std::cout << "Resultado aync: " << resul.get() << std::endl;
}
