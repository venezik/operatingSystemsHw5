#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate  turnaround times for FCFS
void FCFS(vector<Process>& processes) {
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to calculate turnaround times for SJF
void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burst_time < b.burst_time;
        });

    FCFS(processes);
}

// Print results
void printResults(const vector<Process>& processes, const string& scheduling_type) {
    cout << "----------------- " << scheduling_type << " -----------------\n";
    cout << "Process ID | Waiting Time | Turnaround Time\n";
    int total_waiting = 0, total_turnaround = 0;

    for (const auto& process : processes) {
        cout << "     " << process.id << "           |      " << process.waiting_time
            << "                 |        " << process.turnaround_time << "\n";
        total_waiting += process.waiting_time;
        total_turnaround += process.turnaround_time;
    }

    cout << "\nAverage Waiting Time: " << (float)total_waiting / processes.size() << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround / processes.size() << "\n\n";
}

int main() {
    vector<Process> processes = {
        {1, 2, 0, 0},
        {2, 1, 0, 0},
        {3, 8, 0, 0},
        {4, 4, 0, 0},
        {5, 5, 0, 0}
    };

    vector<Process> fcfs_processes = processes;
    vector<Process> sjf_processes = processes;

    FCFS(fcfs_processes);
    printResults(fcfs_processes, "FCFS");

    SJF(sjf_processes);
    printResults(sjf_processes, "SJF");

    return 0;
}