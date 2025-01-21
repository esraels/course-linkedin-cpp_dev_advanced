#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <atomic>

std::atomic_bool ready {};
std::atomic_uint64_t g_count{};
std::atomic_flag winner {};

constexpr uint64_t max_count {1'000'000};
constexpr int max_threads {100};

std::string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length())-3; l > 0; l -= 3){
        s.insert(l, ",");
    }
    return s;
}

void sleep_ms(auto ms){
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;
    sleep_for(milliseconds(ms));
}

void countem(int id){
    while(!ready) std::this_thread::yield;
    for(auto i=0; i < max_count; ++i){
        if (winner.test()) return;
        ++g_count;
    }
    if (!winner.test_and_set()) {
        std::cout << "thread " << id << " won!" << std::endl;
        winner.notify_all();
    }
}

int main(){
    std::list<std::thread> swarm{};
    std::cout << "swarm " << max_threads << std::endl;
    for(auto i = 0; i < max_threads; ++i){
        swarm.emplace_back(countem, i);
    }

    sleep_ms(25);
    std::cout << "Go!" << std::endl;
    ready = true;

    for(auto& t : swarm) t.join();
    std::cout << "global count: " << make_commas(g_count) << std::endl;

    return 0;
}

