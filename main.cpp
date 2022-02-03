#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>

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
    return synonyms[first_word].count(second_word) == 0;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for(const auto& item : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for(const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
            << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

void TestAddSynonyms() {
    {
        Synonyms empty;
        AddSynonyms(empty, "a", "b");
        const Synonyms expected = {
            {"a", {"b"}},
            {"b", {"a"}}
        };
        AssertEqual(empty, expected, "Add to empty");
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
        AssertEqual(synonyms, expected, "Add to synonyms");
    }
    cout << "TestAddSynonyms OK" << endl;
}

void TestCount() {
    {
        Synonyms empty;
        AssertEqual(GetSynonymsCount(empty, "a"), 0u, "count for empty");
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}
        };
        AssertEqual(GetSynonymsCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetSynonymsCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetSynonymsCount(synonyms, "z"), 0u, "count for z");
    }
    cout << "TestCount OK" << endl;
}

void TestAreSynonyms() {
    {
        Synonyms empty;
        Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
        Assert(!AreSynonyms(empty, "a", "b"), "empty b a");
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}},
        };
        Assert(AreSynonyms(synonyms, "a", "b"), "");
        Assert(AreSynonyms(synonyms, "b", "a"), "");
        Assert(AreSynonyms(synonyms, "a", "c"), "");
        Assert(AreSynonyms(synonyms, "a", "b"), "");
        Assert(!AreSynonyms(synonyms, "b", "c"), "");
        Assert(!AreSynonyms(synonyms, "c", "b"), "");
    }
    cout << "TestAreSynonyms OK" << endl;
}

template <class TestFunc>
void RunTest(TestFunc func, const string& test_name) {
    try {
        func();
    } catch (runtime_error& e) {
        cout << test_name << " fail: " << e.what() << endl;
    }
}

int main() {
    RunTest(TestAreSynonyms, "TestAreSynonyms");
    RunTest(TestCount, "TestCount");
    RunTest(TestAddSynonyms, "TestAddSynonyms");
    return 0;

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
