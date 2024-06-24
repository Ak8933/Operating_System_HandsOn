#include <iostream>
#include <thread>
#include <unistd.h> // POSIX sleep function

void TaskA() {
    for (int i = 0; i < 10; ++i) {
        sleep(1);
        std::cout << "Task A: " << i << std::endl;
        fflush(stdout);
    }
}

void TaskB() {
    for (int i = 0; i < 10; ++i) {
        sleep(1);
        std::cout << "Task B: " << i << std::endl;
        fflush(stdout);
    }
}

void TaskC() {
    for (int i = 0; i < 10; ++i) {
        sleep(1);
        std::cout << "Task C: " << i << std::endl;
        fflush(stdout);
    }
}

int main() {
    std::thread t1(TaskA);
    std::thread t2(TaskB);
    std::thread t3(TaskC);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
