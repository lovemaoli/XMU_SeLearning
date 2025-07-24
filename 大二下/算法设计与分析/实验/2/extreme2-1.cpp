#include <iostream>
#include <vector>
using namespace std;
// ·ÖÖÎËã·¨ 
int findMinimum(const std::vector<int>& arr, int start, int end) {
    if (start == end) {
        return arr[start];
    }
    
    int mid = (start + end) / 2;
    int leftMin = findMinimum(arr, start, mid);
    int rightMin = findMinimum(arr, mid + 1, end);
    
    return min(leftMin, rightMin);
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int result = findMinimum(arr, 0, n - 1);
    cout << result << endl;

    return 0;
}

