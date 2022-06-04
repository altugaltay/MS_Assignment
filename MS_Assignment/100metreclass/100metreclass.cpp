#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
std::mutex m;

class Runners {
private:
    int speed;
    int totalRoad;
    int instantLocation;
    int pos;

    

public:

    Runners() {
         pos = 0;
         speed = 0;
         totalRoad = 100;

    }


    void randomSpeed() {
        m.lock();

        srand(time(0));
        speed = (rand() % 5) + 1;

        m.unlock();
    }

    void position() {
        m.lock();

        pos = pos + speed;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (pos > (totalRoad-1) ) {
            std::cout << "Runner finished the race" << std::endl;
            std::cout << "----------------------" << std::endl;
            pos = totalRoad;
        }
        else {
            std::cout << "Runner continues the race" << std::endl;
            std::cout << "----------------------" << std::endl;
        }

        m.unlock();
    }

    void print() {
        m.lock();
    
        std::cout << "Starting Speed: " << speed<<" " << "m/sn" << std::endl; 
        std::cout << "Instant Location(m): " << pos << std::endl;
     
        m.unlock();
    }

 

};

//  Runners object is passed by reference
void thread_task(Runners& o) {
    o.randomSpeed();
    o.print();
    o.position();
}

int main()
{
    Runners runner;
    clock_t time_req;
    std::cout << "Press Enter to Start Race!" << std::endl;
    std::cin.ignore();

        time_req = clock();
    
        std::vector<std::thread> runners;
        for (size_t i = 0; i < 100; i++) {
            runners.push_back(std::thread(thread_task,std::ref(runner)));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        for (size_t i = 0; i < 100; i++) {
            runners[i].join();
        }
        

        time_req = clock() - time_req;
        std::cout << "Time of process: " << time_req/CLOCKS_PER_SEC << std::endl;

        std::cout << "End of race" << std::endl;
        std::cin.ignore();
    return 0;
}
