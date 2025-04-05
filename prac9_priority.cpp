#include <bits/stdc++.h>
using namespace std;

int pid[20], at[20], bt[20], rt[20], pr[20]; // priority array
int wt[20], tat[20], ct[20];
int n;

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
        cout << "Priority (lower number = higher priority): ";
        cin >> pr[i];
        rt[i] = bt[i]; // Set remaining time
    }
}

void preemptivePriorityScheduling() {
    int time = 0, complete = 0, current = -1;
    float total_wt = 0, total_tat = 0;
    bool isDone[20] = {false};

    while (complete < n) {
        int highest = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && pr[i] < highestPriority) {
                highestPriority = pr[i];
                highest = i;
            }
        }

        if (highest != -1) {
            rt[highest]--;
            time++;

            if (rt[highest] == 0) {
                ct[highest] = time;
                tat[highest] = ct[highest] - at[highest];
                wt[highest] = tat[highest] - bt[highest];
                complete++;
                isDone[highest] = true;
            }
        } else {
            time++; // No process is available
        }
    }

    // Output
    cout << "\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << pid[i] << "]\t" << at[i] << "\t" << bt[i] << "\t" << pr[i]
             << "\t\t" << wt[i] << "\t" << tat[i];
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
        cout << "\n===== Preemptive Priority Scheduling Menu =====\n";
        cout << "1. Enter Process Data\n";
        cout << "2. Run Preemptive Priority Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputProcesses();
                break;
            case 2:
                preemptivePriorityScheduling();
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
