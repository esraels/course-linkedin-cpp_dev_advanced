#include <format>
#include <iostream>
#include <chrono>
#include <thread>

using std::this_thread::sleep_for;

using namespace std::chrono_literals;

void wait(int ms){
    sleep_for(std::chrono::milliseconds(ms));
}

template<typename T>
void wait(T dur){
    sleep_for(dur);
}

void funcThread(int id, int loopTime) {

    for(int a = 0; a < 5; a++){
        wait(loopTime);
        std::cout << "thread " << id << ": slept for " << loopTime << "ms" << std::endl;
    }

    std::cout << "thread " << id << ": ended" << std::endl;

}

int main() {
    std::thread t1(funcThread, 1, 100);
    std::thread t2(funcThread, 2, 200);

    t1.detach();
    t2.detach();

    std::cout << "main() will sleep for 2 seconds. " << std::endl;
    wait(2000ms);

    std::cout << "End main()" << std::endl;

    return 0;
}