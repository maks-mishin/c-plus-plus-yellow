// Author : Maks Mishin
// Date : 2/10/2022.
//


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSortDiv3(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    //следующий код заменить
    auto it_first = begin(elements) + elements.size() / 3;
    auto it_second = it_first + elements.size() / 3;

    MergeSort(begin(elements), it_first);
    MergeSort(it_first, it_second);
    MergeSort(it_second, end(elements));

    vector<typename RandomIt::value_type> tempVec;
    // сливаем первые две трети вектора во временный вектор
    std::merge(begin(elements), it_first, it_first, it_second, back_inserter(tempVec));

    std::merge(begin(tempVec), end(tempVec), it_second, end(elements), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSortDiv3(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}