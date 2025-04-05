#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, i, j;
    int pid[20], at[20], bt[20], wt[20], tat[20], ct[20], completed[20];
    float avwt = 0, avtat = 0;

    cout << "Enter total number of processes (maximum 20): ";
    cin >> n;

    // Input process details
    for (i = 0; i < n; i++) {
        cout << "\nEnter details for Process P[" << i + 1 << "]:\n";
        pid[i] = i + 1;
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        completed[i] = 0; // mark all processes as not completed
    }

    int currentTime = 0, totalCompleted = 0;

    while (totalCompleted < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        // Find the process with the shortest burst time among those that have arrived
        for (i = 0; i < n; i++) {
            if (at[i] <= currentTime && completed[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx != -1) {
            wt[idx] = currentTime - at[idx];
            if (wt[idx] < 0) wt[idx] = 0;

            tat[idx] = wt[idx] + bt[idx];
            ct[idx] = currentTime + bt[idx];

            currentTime = ct[idx];
            completed[idx] = 1;
            totalCompleted++;
        } else {
            currentTime++; // No process is ready yet
        }
    }

    // Output
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround";
    for (i = 0; i < n; i++) {
        cout << "\nP[" << pid[i] << "]\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i];
        avwt += wt[i];
        avtat += tat[i];
    }

    avwt /= n;
    avtat /= n;

    cout << fixed << setprecision(2);
    cout << "\n\nAverage Waiting Time: " << avwt;
    cout << "\nAverage Turnaround Time: " << avtat << "\n";

    return 0;
}
