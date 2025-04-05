#include <bits/stdc++.h>
using namespace std;

int pid[20], at[20], bt[20], rt[20]; // rt = remaining time
int wt[20], tat[20], ct[20];
int n, tq; // tq = time quantum

void inputProcesses() {
    cout << "Enter number of processes (max 20): ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nEnter details for Process P[" << pid[i] << "]:\n";
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        rt[i] = bt[i]; // initially, remaining time = burst time
    }

    cout << "\nEnter Time Quantum: ";
    cin >> tq;
}

void roundRobin() {
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    bool visited[20] = {false};

    float total_wt = 0, total_tat = 0;

    // Push the first arriving process to the queue
    queue[rear++] = 0;
    visited[0] = true;

    while (completed < n) {
        int idx = queue[front++];
        if (rt[idx] > 0) {
            // If remaining time is more than time quantum
            if (rt[idx] > tq) {
                time += tq;
                rt[idx] -= tq;
            } else {
                time += rt[idx];
                wt[idx] = time - at[idx] - bt[idx];
                tat[idx] = time - at[idx];
                ct[idx] = time;
                rt[idx] = 0;
                completed++;
            }

            // Add all processes that have arrived and not visited
            for (int i = 0; i < n; i++) {
                if (!visited[i] && at[i] <= time) {
                    queue[rear++] = i;
                    visited[i] = true;
                }
            }

            // If current process is not yet finished, push it back to queue
            if (rt[idx] > 0) {
                queue[rear++] = idx;
            }
        }

        // If queue is empty but not all processes completed, advance time
        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    queue[rear++] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << pid[i] << "]\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << fixed << setprecision(2);
    cout << "\n\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== Round Robin Scheduling Menu =====\n";
        cout << "1. Enter Process Data\n";
        cout << "2. Run Round Robin Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputProcesses();
                break;
            case 2:
                roundRobin();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
