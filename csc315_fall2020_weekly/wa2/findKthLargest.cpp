#include <algorithm>
#include <vector>

using namespace std;

void bubble_sort(vector<int> &arr, int n) {
    // Base Case
    if (n == 1) 
        return;
    
    // Move largest value to the end
    for (int i = 0; i < n-1; i++)
        if (arr[i] > arr[i+1])
            swap(arr[i], arr[i+1]);
    
    // We know largest value is at n, decrement by 1
    bubble_sort(arr, n-1); 
}

int findKthLargest(vector<int> &arr, int k) {
    int size = arr.size();

    // Sort all integers within the vector
    bubble_sort(arr, size);
   
    // Return largest int if k <= 0
    if (k <= 0)
       return arr[size-1];

    // Return Kth largest int
    return k > int(arr.size()) ? arr[0] : arr[size-k];
}
