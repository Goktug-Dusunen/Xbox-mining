#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const string POOL_URL = "xna.2miners.com:2222";
const string WALLET_ADDRESS = "YOUR_WALLET_ADDRESS";

const int NUM_THREADS = 4;

atomic<bool> stop_flag(false);

void worker(int thread_id) {
    auto start_time = chrono::steady_clock::now();

    long long total_work = 0;

    while (!stop_flag) {
        total_work++;
    }

    auto end_time = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    double power = total_work / (duration / 1000.0); 


    cout << "İşçi " << thread_id << ": Toplam iş miktarı = " << total_work << endl;
    cout << "İşçi " << thread_id << ": Geçen süre (ms) = " << duration << endl;
    cout << "İşçi " << thread_id << ": Güç üretimi (iş/saniye) = " << power << endl;
}

int main() {
    cout << "Ana işlev: Başlatılıyor..." << endl;

    vector<thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(worker, i));
    }

    this_thread::sleep_for(chrono::seconds(10));

    stop_flag = true;
    for (thread& thread : threads) {
        thread.join();
    }

    cout << "Ana işlev: Sonlandırılıyor..." << endl;

    return 0;
}
