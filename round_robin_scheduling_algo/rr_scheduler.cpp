#include<iostream> 
using namespace std; 

void calculateWaitingTime(int procs[], int numProcs, int burstTimes[], int waitTimes[], int timeQuantum) { 
	int remainingBurst[numProcs]; 
	for (int i = 0; i < numProcs; i++) 
		remainingBurst[i] = burstTimes[i]; 

	int currentTime = 0; 

	while (true) { 
		bool allDone = true; 

		for (int i = 0; i < numProcs; i++) { 
			if (remainingBurst[i] > 0) { 
				allDone = false; 
				if (remainingBurst[i] > timeQuantum) { 
					currentTime += timeQuantum; 
					remainingBurst[i] -= timeQuantum; 
				} else { 
					currentTime += remainingBurst[i]; 
					waitTimes[i] = currentTime - burstTimes[i]; 
					remainingBurst[i] = 0; 
				} 
			} 
		} 

		if (allDone) 
			break; 
	} 
} 

void calculateTurnAroundTime(int procs[], int numProcs, int burstTimes[], int waitTimes[], int turnAroundTimes[]) { 
	for (int i = 0; i < numProcs; i++) 
		turnAroundTimes[i] = burstTimes[i] + waitTimes[i]; 
} 

void calculateAverageTime(int procs[], int numProcs, int burstTimes[], int timeQuantum) { 
	int waitTimes[numProcs], turnAroundTimes[numProcs], totalWait = 0, totalTurnAround = 0; 

	calculateWaitingTime(procs, numProcs, burstTimes, waitTimes, timeQuantum); 
	calculateTurnAroundTime(procs, numProcs, burstTimes, waitTimes, turnAroundTimes); 

	cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n"; 
	for (int i = 0; i < numProcs; i++) { 
		totalWait += waitTimes[i]; 
		totalTurnAround += turnAroundTimes[i]; 
		cout << " " << i+1 << "\t\t" << burstTimes[i] << "\t\t" << waitTimes[i] << "\t\t" << turnAroundTimes[i] << endl; 
	} 

	cout << "Average waiting time = " << (float)totalWait / (float)numProcs << endl; 
	cout << "Average turnaround time = " << (float)totalTurnAround / (float)numProcs << endl; 
} 

int main() { 
	int processes[] = { 1, 2, 3 }; 
	int numProcs = sizeof processes / sizeof processes[0]; 
	int burstTimes[] = {10, 5, 8}; 
	int timeQuantum = 2; 
	calculateAverageTime(processes, numProcs, burstTimes, timeQuantum); 
	return 0; 
} 
