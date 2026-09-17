#include <iostream>

void test1(){
	int *ptr;
	
	ptr = new int[10];

}

void test2(){
	int *ptr;
	
	ptr = new int[10];
	delete [] ptr;

}

int main(){
	//test1();
	test2();	
}
