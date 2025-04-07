#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, disk_size, head, total_seek = 0;
    cout << "Enter the size of disk: ";
    cin >> disk_size;

    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
        if (requests[i] > disk_size) {
            cout << "Invalid request: exceeds disk size.\n";
            return 0;
        }
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int direction;
    cout << "Enter direction (0 = Left, 1 = Right): ";
    cin >> direction;

    // Separate requests to left and right of head
    vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<int> seek_sequence;
    int current = head;

    // LOOK scheduling
    if (direction == 1) { // Moving right first
        for (int r : right) {
            total_seek += abs(current - r);
            current = r;
            seek_sequence.push_back(r);
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            total_seek += abs(current - left[i]);
            current = left[i];
            seek_sequence.push_back(current);
        }
    } else { // Moving left first
        for (int i = left.size() - 1; i >= 0; i--) {
            total_seek += abs(current - left[i]);
            current = left[i];
            seek_sequence.push_back(current);
        }
        for (int r : right) {
            total_seek += abs(current - r);
            current = r;
            seek_sequence.push_back(current);
        }
    }

    // Output the seek sequence
    cout << "\nSeek Sequence: " << head;
    for (int r : seek_sequence)
        cout << " -> " << r;

    cout << "\nTotal Head Movements (LOOK): " << total_seek << "\n";

    return 0;
}
