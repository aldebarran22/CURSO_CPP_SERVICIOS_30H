/*

	Productor - Consumidor con thread:
*/


#include <thread>
#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::queue<int> cola;
std::condition_variable cv;
std::mutex mutex_cola;


void productor();
void consumidor();

int main(){

	std::srand(std::time(0));

	std::thread pro {productor};
	std::thread con {consumidor};

	pro.join();
	con.join();
}


void productor(){
	int item;

	for (int i = 0 ; i < 10 ; i++){
		item = std::rand() % 100;
		
		std::cout << "P:" << item << std::endl;

		std::unique_lock<std::mutex> l{mutex_cola};
		cola.push(item);

		cv.notify_one();

		std::this_thread::sleep_for(std::chrono::seconds(rand()%2));
	}		

}

void consumidor(){
	
	for (int i = 0 ; i < 10 ; i++){
		std::unique_lock<std::mutex> l{mutex_cola};
		while (cola.empty()) cv.wait(l);

		auto item = cola.front();
		cola.pop();
		l.unlock();
	
		std::cout << "C:" << item << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(rand()%2));

	}

}
