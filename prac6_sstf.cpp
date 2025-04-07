#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, disk_size, head;
    cout << "Enter the size of disk: ";
    cin >> disk_size;

    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> requests(n);
    map<int, int> mpp;
    cout << "Enter the requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
        if (requests[i] > disk_size) {
            cout << "Invalid request at position " << i << ": " << requests[i] << "\n";
            return 0;
        }
        mpp[requests[i]]++;
    }

    cout << "Enter the head position: ";
    cin >> head;

    vector<int> sequence;
    sequence.push_back(head);
    int temp = head, total_seek = 0, count = 0;

    while (count < n) {
        int min_diff = INT_MAX, next = -1;

        for (auto &q : mpp) {
            int d = abs(q.first - temp);
            if (d < min_diff) {
                min_diff = d;
                next = q.first;
            }
        }

        sequence.push_back(next);
        total_seek += min_diff;
        temp = next;
        mpp[next]--;

        if (mpp[next] == 0)
            mpp.erase(next);

        count++;
    }

    cout << "\nSeek Sequence: " << sequence[0];
    for (int i = 1; i < sequence.size(); i++) {
        cout << " -> " << sequence[i];
    }

    cout << "\nTotal Head Movements: " << total_seek;
    cout << "\nAverage Head Movement: " << fixed << setprecision(2) << (float)total_seek / n << "\n";

    return 0;
}
