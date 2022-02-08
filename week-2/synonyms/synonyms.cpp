// Author : Maks Mishin
// Date 2/6/2022

#include <iostream>
#include <string>
#include <sstream>
#include "tests_synonyms.h"

using namespace std;

int main() {
    TestAll();

    int count_operations;
    cin >> count_operations;

    Synonyms synonyms;

    for (int i = 0; i < count_operations; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {
            string first_word, second_word;
            cin >> first_word >> second_word;
            AddSynonyms(synonyms, first_word, second_word);

        } else if (operation_code == "COUNT") {
            string word;
            cin >> word;
            cout << GetSynonymsCount(synonyms, word) << endl;

        } else if (operation_code == "CHECK") {

            string first_word, second_word;
            cin >> first_word >> second_word;

            if (AreSynonyms(synonyms, first_word, second_word)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }

        }
    }

    return 0;
}


