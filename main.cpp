#include <format>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

using std::chrono::steady_clock;
using std::chrono::duration;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;

using namespace std::chrono_literals;

int main(){

    cout << "let's wait a bit.." << endl;

    auto timeStart = steady_clock::now();
    cout << "sleep for 2.5 seconds" << endl;
    sleep_for(2s + 500ms);

    cout << "sleep for 3 seconds" << endl;
    sleep_until(steady_clock::now() + 3s);

    duration<double> dur = steady_clock::now() - timeStart;
    cout << "Total duration: " << dur.count() << endl;

    cout << "Hello meow" << endl;

    return 0;
}