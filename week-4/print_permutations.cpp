// Author : Maks Mishin
// Date : 2/9/2022.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
void PrintRange(
        T range_begin,
        T range_end) {
    for (auto it = range_begin; it != range_end; it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void PrintPermutations(const int N) {
    vector<int> nums;
    for(int i = N; i >= 1; i--) {
        nums.push_back(i);
    }
    PrintRange(begin(nums), end(nums));
    while(prev_permutation(begin(nums), end(nums))) {
        PrintRange(begin(nums), end(nums));
    }
}

int main() {
    int N;
    cin >> N;
    PrintPermutations(N);
    return 0;
}
