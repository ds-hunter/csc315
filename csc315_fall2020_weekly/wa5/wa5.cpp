#include <iostream>
#include <iomanip>
#include <chrono>
#include <unordered_set>
#include <set>

using namespace std;

template<class setType>
bool isSubset(int *subset, setType set, int size);

int main() {
    int n, m, value, *subset;
    bool valid;
    chrono::duration<double> unorderedTime, orderedTime;
    chrono::system_clock::time_point startTime, endTime;
    unordered_set<int> ulist;
    set<int> list;

    // Get subset values
    cin >> m;
    subset = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> subset[i];
    }

    // Get list values
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.insert(value);
        ulist.insert(value);
    }
    
    // Test for valid subset using ordered list method and calculate its runtime
    startTime = chrono::system_clock::now();
    valid = isSubset(subset, list, m);
    endTime = chrono::system_clock::now();
    orderedTime = endTime - startTime;

    // Calculate runtime of unordered list method
    startTime = chrono::system_clock::now();
    valid = isSubset(subset, ulist, m);
    endTime = chrono::system_clock::now();
    unorderedTime = endTime - startTime;
    
    cout << fixed << setprecision(10) << "Set Time: " << orderedTime.count() 
         << " USet Time: " << unorderedTime.count() << endl;
    cout << (valid ? "Yes" : "No");
    return 0;
}

template<class setType>
bool isSubset(int *subset, setType set, int size) {
    for (int i = 0; i < size; i++) {
        if (set.find(subset[i]) == set.end()) return false;
    }
    return true;
}

