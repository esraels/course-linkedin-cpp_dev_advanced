#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std::chrono_literals;

constexpr size_t num_items {10};
constexpr auto delay_time {250ms};

std::mutex p_mtx {};
std::mutex c_mtx {};
std::deque<size_t> q{};
std::atomic_flag finished{};

void sleep_ms(const auto& delay){
    std::this_thread::sleep_for(delay);
}

void producer(){
    for(size_t i{}; i < num_items; ++i){
        sleep_ms(delay_time);
        std::cout << "push " << i << " on the queue" << std::endl;
        std::lock_guard<std::mutex> l{p_mtx};
        q.push_back(i);
    }
    std::lock_guard<std::mutex> l{p_mtx};
    finished.test_and_set();
}

void consumer() {
    while(!finished.test()){
        sleep_ms(delay_time * 3);
        std::lock_guard<std::mutex> l{c_mtx};
        while(!q.empty()) {
            std::cout << "pop " << q.front() << " from the queue" << std::endl;
            q.pop_front();
        }
    }
}

int main(){
    std::thread t1{producer};
    std::thread t2{consumer};
    t1.join();
    t2.join();
    std::cout << "finished!" << std::endl;


    return 0;

}


