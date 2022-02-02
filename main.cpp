#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cassert>

using namespace std;

using Synonyms = map<string, set<string>>;

void AddSynonyms(Synonyms& synonyms, const string& first_word,
                 const string& second_word) {
    synonyms[first_word].insert(second_word);
    synonyms[second_word].insert(first_word);
}

size_t GetSynonymsCount(Synonyms& synonyms,
                        const string& word) {
    return synonyms[word].size();
}

bool AreSynonyms(Synonyms& synonyms, const string& first_word,
                 const string& second_word) {
    return synonyms[first_word].count(second_word) == 1;
}

void TestAddSynonyms() {
    {
        Synonyms empty;
        AddSynonyms(empty, "a", "b");
        const Synonyms expected = {
            {"a", {"b"}},
            {"b", {"a"}}
        };
        assert(empty == expected);
    }
    {
        Synonyms synonyms = {
            {"a", {"b"}},
            {"b", {"a", "c"}},
            {"c", {"b"}}
        };
        AddSynonyms(synonyms, "a", "c");
        Synonyms expected = {
            {"a", {"b", "c"}},
            {"b", {"a", "c"}},
            {"c", {"b", "a"}}
        };
        assert(synonyms == expected);
    }
    cout << "TestAddSynonyms OK" << endl;
}

void TestCount() {
    {
        Synonyms empty;
        assert(GetSynonymsCount(empty, "a") == 0);
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}
        };
        assert(GetSynonymsCount(synonyms, "a") == 2);
        assert(GetSynonymsCount(synonyms, "b") == 1);
        assert(GetSynonymsCount(synonyms, "z") == 0);
    }
    cout << "TestCount OK" << endl;
}

void TestAreSynonyms() {
    {
        Synonyms empty;
        assert(!AreSynonyms(empty, "a", "b"));
        assert(!AreSynonyms(empty, "a", "b"));
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}},
        };
        assert(AreSynonyms(synonyms, "a", "b"));
        assert(AreSynonyms(synonyms, "b", "a"));
        assert(AreSynonyms(synonyms, "a", "c"));
        assert(AreSynonyms(synonyms, "a", "b"));
        assert(!AreSynonyms(synonyms, "b", "c"));
        assert(!AreSynonyms(synonyms, "c", "b"));
    }
    cout << "TestAreSynonyms OK" << endl;
}

void TestAll(){
    TestCount();
    TestAreSynonyms();
    TestAddSynonyms();
}

int main() {
//    TestAll();
//    return 0;

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
