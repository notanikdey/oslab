#include <bits/stdc++.h>
using namespace std;

// Shortest Seek Time First Algorithm
void SSTF(const vector<int>& requests, int head) {
    int n = requests.size();
    vector<bool> visited(n, false);
    int seek_time = 0;
    int current = head;
    
    cout << "SSTF Seek Sequence: " << head;
    
    // Process all requests
    for (int i = 0; i < n; i++) {
        int min_diff = INT_MAX;
        int next_index = -1;
        
        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int diff = abs(requests[j] - current);
                if (diff < min_diff) {
                    min_diff = diff;
                    next_index = j;
                }
            }
        }
        
        // Mark as visited and update seek time
        visited[next_index] = true;
        seek_time += min_diff;
        current = requests[next_index];
        
        cout << " -> " << current;
    }
    
    cout << "\nTotal Seek Time (SSTF): " << seek_time << endl;
}

// LOOK Algorithm
void LOOK(const vector<int>& requests, int head, bool direction) {
    vector<int> left, right;
    int seek_time = 0;
    int current = head;
    
    // Separate requests into left and right of head
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else if (r > head) right.push_back(r);
        // Skip if r == head since we're already there
    }
    
    // Sort both arrays
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    cout << "LOOK Seek Sequence: " << head;
    
    // Process requests based on direction
    if (direction) { // Right direction first
        // Process all requests to the right
        for (int r : right) {
            seek_time += abs(current - r);
            current = r;
            cout << " -> " << current;
        }
        
        // Then process all requests to the left in reverse order
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_time += abs(current - left[i]);
            current = left[i];
            cout << " -> " << current;
        }
    } else { // Left direction first
        // Process all requests to the left in reverse order
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_time += abs(current - left[i]);
            current = left[i];
            cout << " -> " << current;
        }
        
        // Then process all requests to the right
        for (size_t i = 0; i < right.size(); i++) {
            seek_time += abs(current - right[i]);
            current = right[i];
            cout << " -> " << current;
        }
    }
    
    cout << "\nTotal Seek Time (LOOK): " << seek_time << endl;
}

int main() {
    vector<int> requests;
    int head = 0;
    int choice;
    
    do {
        cout << "\n===== Disk Scheduling Menu =====\n";
        cout << "1. Enter Requests & Head Position\n";
        cout << "2. Run SSTF Algorithm\n";
        cout << "3. Run LOOK Algorithm\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int n;
                cout << "Enter number of disk requests: ";
                cin >> n;
                
                requests.clear();
                requests.resize(n);
                
                cout << "Enter the disk requests: ";
                for (int i = 0; i < n; i++) 
                    cin >> requests[i];
                
                cout << "Enter initial head position: ";
                cin >> head;
                break;
            }
            
            case 2:
                if (!requests.empty()) 
                    SSTF(requests, head);
                else 
                    cout << "Please enter requests first!\n";
                break;
                
            case 3:
                if (!requests.empty()) {
                    int dir;
                    cout << "Enter initial direction (0=Left, 1=Right): ";
                    cin >> dir;
                    LOOK(requests, head, dir);
                } else {
                    cout << "Please enter requests first!\n";
                }
                break;
                
            case 4:
                cout << "Exiting program...\n";
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}