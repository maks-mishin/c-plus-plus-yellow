// Author : Maks Mishin
// Date : 2/7/2022.

#include <map>
#include <string>
#include "UnitTestFramework.h"

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        }
        else if (first_name.empty()) {
            return last_name + " with unknown first name";
        }
        else if (last_name.empty()) {
            return first_name + " with unknown last name";
        }
        else {
            return first_name + " " + last_name;
        }
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
};

void TestGetFullName() {
    Person person;
    string first_name = "A", last_name = "B";
    int year = 2022;
    string expected = first_name + " " + last_name;

    person.ChangeFirstName(year, first_name);
    person.ChangeLastName(year, last_name);
    AssertEqual(person.GetFullName(year), expected, "test GetFullName");
}

void TestIncognito() {
    Person person;
    string expected = "Incognito";
    int year = 2022;
    AssertEqual(person.GetFullName(year), expected, "test Incognito");
}

void TestFirstWithoutLast() {
    Person person;
    string name = "Maks";
    int year = 2022;
    string expected = name + " with unknown last name";
    person.ChangeFirstName(year, name);
    AssertEqual(person.GetFullName(year), expected, "test first name without last");
}

void TestLastWithoutFirst() {
    Person person;
    string name = "Maks";
    int year = 2022;
    string expected = name + " with unknown first name";
    person.ChangeLastName(year, name);
    AssertEqual(person.GetFullName(year), expected, "test last name without first");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestFirstWithoutLast, "TestFirstWithoutLast");
    runner.RunTest(TestLastWithoutFirst, "TestLastWithoutFirst");
    runner.RunTest(TestGetFullName, "TestGetFullName");
    return 0;
}

