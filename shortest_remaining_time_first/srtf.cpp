#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int remaining; // Remaining time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;   // Waiting time
};

bool arrivalComparator(Process a, Process b) {
    return a.arrival < b.arrival;
}

bool remainingComparator(Process a, Process b) {
    if (a.remaining == b.remaining) {
        return a.arrival < b.arrival;
    }
    return a.remaining < b.remaining;
}

void calculateTimes(vector<Process> &processes) {
    int n = processes.size();
    int time = 0;
    int completed = 0;
    vector<Process> readyQueue;

    while (completed != n) {
        // Add newly arrived processes to the ready queue
        for (auto &p : processes) {
            if (p.arrival <= time && p.remaining > 0 && find(readyQueue.begin(), readyQueue.end(), p) == readyQueue.end()) {
                readyQueue.push_back(p);
            }
        }

        if (!readyQueue.empty()) {
            // Sort ready queue by remaining time
            sort(readyQueue.begin(), readyQueue.end(), remainingComparator);

            // Get the process with the shortest remaining time
            auto &current = readyQueue.front();
            time++;
            current.remaining--;

            if (current.remaining == 0) {
                current.completion = time;
                current.turnaround = current.completion - current.arrival;
                current.waiting = current.turnaround - current.burst;
                completed++;

                // Remove process from the ready queue
                readyQueue.erase(readyQueue.begin());
            }
        } else {
            time++; // If no process is ready, increment time
        }
    }
}

void printProcesses(const vector<Process> &processes) {
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 8, 8, 0, 0, 0},
        {2, 1, 4, 4, 0, 0, 0},
        {3, 2, 9, 9, 0, 0, 0},
        {4, 3, 5, 5, 0, 0, 0},
    };

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), arrivalComparator);

    // Calculate times for each process
    calculateTimes(processes);

    // Print the results
    printProcesses(processes);

    return 0;
}
