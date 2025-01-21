#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

void sleepms(const unsigned ms){
    using millis = std::chrono::milliseconds;
    std::this_thread::sleep_for(millis(ms));
}

void thread_func(const int n){
    cout << "This is t" << n << endl;
    auto slp_dur = 100*n;

    for(auto i = 0; i < 5; ++i){
        sleepms(slp_dur);
        cout << "t" << n << "(" << slp_dur << "): loop " << (i+1) << endl;
    }
    cout << "Finishing t" << n << endl;

}

int main(){
    thread t1(thread_func, 1);
    thread t2(thread_func, 2);
    t1.detach();
    t2.detach();

    cout << "main() sleep 2 sec" << endl;
    sleepms(2000);

    cout << "end of main()" << endl;

    return 0;
}
