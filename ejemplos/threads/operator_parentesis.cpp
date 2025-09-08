/*

Prueba con el operador ()

*/


#include <iostream>


class Printer {

	int numero;


	public:
		Printer(int numero=0):numero(numero){}
		void operator()(){
			std::cout << "numero:" << numero << std::endl;
		}
		~Printer(){}
};



int main(){
	Printer pr(8);

	pr();

}
