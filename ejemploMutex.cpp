#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex global

void printNumbers(int id) {
    // Bloquear el mutex usando lock_guard
    std::lock_guard<std::mutex> lock(mtx);
    
    // Sección crítica: solo un hilo puede ejecutar esto a la vez
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << id << " prints: " << i << std::endl;
    } // Cuando la función termine, el mutex se desbloqueará automáticamente.
}

int main() {
    std::thread t1(printNumbers, 1);
    std::thread t2(printNumbers, 2);

    t1.join();
    t2.join();
    return 0;
}
