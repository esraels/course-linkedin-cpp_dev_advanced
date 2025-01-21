#include <format>
#include <list>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::chrono::steady_clock;
using dur_t = std::chrono::duration<double>;

struct process_result {
    dur_t dur{};
    uint64_t count{};
};

void count_primes(const uint64_t& targetNum, std::promise<process_result> pval) {
    process_result result{};
    constexpr auto isprime = [](uint64_t n){
        for(uint64_t i{2}; i < n/2; ++i){
            if(n%i == 0) return false;
        }
        return true;
    };
    uint64_t start{2};
    uint64_t end{targetNum};
    auto time_start = steady_clock::now();
    for(auto i = start; i <= end; ++i){
        if(isprime(i)) ++result.count;
    }
    result.dur = steady_clock::now() - time_start;
    pval.set_value(result);
}

int main(){
    constexpr uint64_t max_prime {0x1FFFF};
    constexpr size_t num_threads{15};
    std::list<std::future<process_result>> listThreads;
    auto time_start = steady_clock::now();
    cout << "start parallel counting on number of primes:" << endl;
    for(auto i = num_threads; i; --i){
        //listThreads.emplace_back(std::async(count_primes, max_prime));
        std::promise<process_result> promise_obj{};
        auto future_obj = promise_obj.get_future();
        listThreads.emplace_back(std::move(future_obj));
        std::thread t(count_primes, max_prime, std::move(promise_obj));
        t.detach();
    }

    for(auto& res : listThreads){
        static auto i = 0;
        auto [dur, count] = res.get();
        cout << "thread " << ++i << ": found " << count << " primes in " << dur.count() << "s" << endl;
    }

    dur_t main_duration{steady_clock::now() - time_start};
    cout << "total duration: " << main_duration.count() << "s" << endl;

    return 0;
}