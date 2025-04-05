#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    int bt[20], wt[20], tat[20], at[20];
    float avwt = 0, avtat = 0;

    cout << "Enter total number of processes (maximum 20): ";
    cin >> n;

    cout << "\nEnter Arrival Times:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P[" << i+1 << "] Arrival Time: ";
        cin >> at[i];
    }

    cout << "\nEnter Burst Times:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P[" << i+1 << "] Burst Time: ";
        cin >> bt[i];
    }

    // Sorting based on Arrival Time
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0); // Initialize index list: 0,1,2,...,n-1
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return at[a] < at[b];
    });

    // First process
    wt[idx[0]] = 0;
    int completion_time = at[idx[0]] + bt[idx[0]];
    tat[idx[0]] = bt[idx[0]];

    // Remaining processes
    for (int i = 1; i < n; i++) {
        int prev = idx[i-1];
        int curr = idx[i];

        // Waiting Time = Start Time - Arrival Time
        int start_time = max(completion_time, at[curr]);
        wt[curr] = start_time - at[curr];
        tat[curr] = wt[curr] + bt[curr];
        completion_time = start_time + bt[curr];
    }

    // Output
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << i+1 << "]\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i];
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
