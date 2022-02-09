// Author : Maks Mishin
// Date : 2/9/2022.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result = {};
    auto begin_word = s.begin();
    string word;
    for (auto it = s.begin(); it != s.end(); it++) {
        if (*it == ' ') {
            word = string(begin_word, it);
            result.push_back(word);
            begin_word = it + 1;
        }
    }
    word = string (begin_word, s.end());
    result.push_back(word);
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}

