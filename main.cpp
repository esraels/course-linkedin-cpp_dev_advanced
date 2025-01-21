#include <format>
#include <list>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::chrono::steady_clock;
using secs = std::chrono::duration<double>;

struct prime_time {
    secs dur{};
    uint64_t count{};
};

prime_time count_primes(const uint64_t& max) {
    prime_time ret{};
    constexpr auto isprime = [](uint64_t n){
        for(uint64_t i {2}; i < n/2; ++i){
            if(n%i == 0) return false;
        }
        return true;
    };
    uint64_t start{2};
    uint64_t end{max};
    auto time_thread_start = steady_clock::now();
    for(auto i = start; i <= end; ++i){
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - time_thread_start;
    return ret;
}

int main(){
    constexpr uint64_t max_prime {0x1FFFF};
    constexpr size_t num_threads{15};
    std::list<std::future<prime_time>> swarm;

    cout << "start parallel primes" << endl;
    auto time_start = steady_clock::now();
    for(auto i = num_threads; i; --i){
        uint64_t targetNum = max_prime;
        swarm.emplace_back(std::async(count_primes, targetNum));
    }

    for(auto& f : swarm){
        static auto i = 0;
        auto [dur, count] = f.get();
        cout << "thread " << ++i << ": found " << count << " primes in " << dur.count() << "s" << endl;
    }

    secs dur_total{steady_clock::now() - time_start};
    cout << "total duration: " << dur_total.count() << "s" << endl;


}
