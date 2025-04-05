#include <bits/stdc++.h>
using namespace std;

int n, m; // Number of processes and resources
int allocation[10][10], max_need[10][10], need[10][10], available[10];
bool finished[10];

void inputData() {
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter Max Need Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max_need[i][j];

    cout << "\nEnter Available Resources: ";
    for (int j = 0; j < m; j++)
        cin >> available[j];

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_need[i][j] - allocation[i][j];

    fill(finished, finished + n, false); // Reset process completion status
}

bool isSafeSequence(vector<int>& safeSequence) {
    int work[10];
    copy(available, available + m, work);

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence.push_back(i);
                    finished[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) return false; // No process could execute, deadlock detected
    }
    return true;
}

void runBankersAlgorithm() {
    vector<int> safeSequence;
    if (isSafeSequence(safeSequence)) {
        cout << "\nSafe Sequence: ";
        for (int i = 0; i < safeSequence.size(); i++)
            cout << "P[" << safeSequence[i] << "] ";
        cout << "\n";
    } else {
        cout << "\nThere is a deadlock in the system.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== Banker's Algorithm Menu =====\n";
        cout << "1. Enter Process & Resource Data\n";
        cout << "2. Check for Safe Sequence\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputData();
                break;
            case 2:
                runBankersAlgorithm();
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
