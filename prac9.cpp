#include <bits/stdc++.h>
using namespace std;

int pid[20], at[20], bt[20], rt[20]; // remaining time
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
        rt[i] = bt[i]; // set remaining time
    }
}

void srtfScheduling() {
    int complete = 0, time = 0, shortest = -1;
    int min_rt = INT_MAX;
    bool found = false;

    float total_wt = 0, total_tat = 0;
    bool isDone[20] = {false};

    while (complete < n) {
        shortest = -1;
        min_rt = INT_MAX;
        found = false;

        // Find the process with shortest remaining time at current time
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            time++; // no process has arrived yet
            continue;
        }

        // Execute the shortest process for 1 unit
        rt[shortest]--;
        time++;

        // If process is completed
        if (rt[shortest] == 0) {
            complete++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            isDone[shortest] = true;
        }
    }

    // Output
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
        cout << "\n===== SRTF Scheduling Menu =====\n";
        cout << "1. Enter Process Data\n";
        cout << "2. Run SRTF Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputProcesses();
                break;
            case 2:
                srtfScheduling();
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
