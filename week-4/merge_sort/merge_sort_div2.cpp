// Author : Maks Mishin
// Date : 2/10/2022.
//


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSortDiv2(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto it_mid = begin(elements) + elements.size() / 2;

    MergeSort(begin(elements), it_mid);
    MergeSort(it_mid, end(elements));

    std::merge(begin(elements), it_mid, it_mid, end(elements), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSortDiv2(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
