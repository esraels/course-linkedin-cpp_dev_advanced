#include <iostream>
#include <chrono>
#include <thread>

void funcThread(int id, int loopTime) {

    for(int a = 0; a < 5; a++){
        auto sleeptime = std::chrono::milliseconds(loopTime);
        std::this_thread::sleep_for(sleeptime);
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

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "End main()" << std::endl;
    

    return 0;
}