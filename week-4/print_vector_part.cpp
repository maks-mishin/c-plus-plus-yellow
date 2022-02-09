// Author : Maks Mishin
// Date : 2/8/2022.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto first_negative_it = find_if(
            numbers.begin(), numbers.end(), [](int number) { return number < 0; }
    );
    for (auto it = first_negative_it - 1; it != numbers.begin() - 1; it--) {
        cout << *it << " ";
    }
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}


