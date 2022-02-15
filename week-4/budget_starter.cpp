// Author : Maks Mishin
// Date 2/10/2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <ctime>
#include <sstream>

#include "../week-2/unit_test_framework/unit_test_framework.h"

using namespace std;

struct Day {
    int value;
    explicit Day(int new_value) {
        value = new_value;
    }
};

struct Month {
    int value;
    explicit Month(int new_value) {
        value = new_value;
    }
};

struct Year {
    int value;
    explicit Year(int new_value) {
        value = new_value;
    }
};

struct Date {
    int day{};
    int month{};
    int year{};
    Date() = default;
    Date(Day new_day, Month new_month, Year new_year) {
        day = new_day.value;
        month = new_month.value;
        year = new_year.value;
    }
};

// returns difference between two dates in days
auto DiffDates(const Date& date_from, const Date& date_to) {
    std::tm dur[2] {
            {0,0,0, date_from.day,date_from.month - 1,date_from.year - 1900},
            {0,0,0, date_to.day, date_to.month - 1, date_to.year - 1900}
    };
    std::time_t t1 {std::mktime(dur)}, t2 {std::mktime(dur+1)};
    if ( t1 != (std::time_t)(-1) && t2 != (std::time_t)(-1) ) {
        return std::difftime(t2, t1) / (60 * 60 * 24);
    }
    return 0.0;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

Date ConvertStringToDate(const string& date_string) {
    Date result_date;
    auto it_year = find(begin(date_string), end(date_string), '-');
    result_date.year = stoi(string(begin(date_string), it_year));

    auto it_month = find(it_year+1, end(date_string), '-');
    result_date.month = stoi(string(it_year+1, it_month));

    result_date.day = stoi(string(it_month+1, end(date_string)));
    return result_date;
}

double ComputeIncome(map<Date, double>& budget, const Date& date_from, const Date& date_to) {
    if (date_to < date_from) {
        throw invalid_argument("argument 'date_to' should be great of 'date_from'");
    }

    // if budget.count(date) == 0 => insert pair{date, 0}
    if (budget.count(date_from) == 0)
        budget[date_from] = 0;
    if (budget.count(date_to) == 0)
        budget[date_to] = 0;

    auto it_from = find_if(begin(budget), end(budget),
                           [&date_from](const pair<Date, double>& p) {
                               return p.first == date_from;
                           });
    auto it_to = find_if(begin(budget), end(budget),
                         [&date_to](const pair<Date, double>& p) {
                             return p.first == date_to;
                         });

    double income = 0.0;
    income = accumulate(it_from, next(it_to), 0.0,
                        [](double value, const std::map<Date, double>::value_type& p) {
                            return value + p.second;
                        });

    return income;
}

bool IsLeapYear(int year) {
    return year % 4 == 0 and year % 100 != 0 or year % 400 == 0;
}

int DaysOfMonth(const Date& date) {
    vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeapYear(date.year))
        days[1] = 29;
    return days[date.month - 1];
}

Date IncDate(const Date& date)
{
    Date result = date;
    if (result.day < DaysOfMonth(result)) {
        result.day++;
    }
    else {
        result.day = 1;

        if( result.month < 12 ) {
            result.month++;
        }
        else {
            result.month = 1;
            result.year++;
        }
    }
    return result;
}

void Earn(map<Date, double>& budget, const Date& date_from, const Date& date_to, int value) {
    if (date_to < date_from) {
        throw invalid_argument("argument 'date_to' should be great of 'date_from'");
    }
    Date tempDate;
    tempDate = date_from;

    auto count_days = DiffDates(date_from, date_to) + 1; // разница между датами в днях
    auto part_value = value / count_days;

    for(int i = 0; i < count_days; i++) {
        if (budget.count(tempDate) > 0) {
            budget[tempDate] += part_value;
        }
        else {
            budget[tempDate] = part_value;
        }
        tempDate = IncDate(tempDate);
    }
}

void TestAuthor() {
    map<Date, double> budget;
    double income;
    Earn(budget, ConvertStringToDate("2000-01-02"), ConvertStringToDate("2000-01-06"), 20);
    income = ComputeIncome(budget, ConvertStringToDate("2000-01-01"), ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 20, "author test income 20");

    income = ComputeIncome(budget, ConvertStringToDate("2000-01-01"), ConvertStringToDate("2000-01-03"));
    AssertEqual(income, 8, "author test income 8");

    Earn(budget, ConvertStringToDate("2000-01-03"), ConvertStringToDate("2000-01-03"), 10);
    income = ComputeIncome(budget, ConvertStringToDate("2000-01-01"), ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 30, "author test income 30");
}

void TestFirst() {
    map<Date, double> budget;
    double income;
//    test zero income
    Earn(budget, ConvertStringToDate("2000-01-01"), ConvertStringToDate("2000-01-01"), 0);
    income = ComputeIncome(budget, ConvertStringToDate("2000-01-01"), ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 0, "first test income 0");

//    test income for several months
    Earn(budget, ConvertStringToDate("2000-01-17"), ConvertStringToDate("2000-02-01"), 900);
    income = ComputeIncome(budget, ConvertStringToDate("2000-01-17"), ConvertStringToDate("2000-02-01"));
    AssertEqual(income, 900, "first test income 900");
}

int main() {
//    TestRunner runner;
//    runner.RunTest(TestAuthor, "TestAuthor");
//    runner.RunTest(TestFirst, "TestFirst");
    cout.precision(25);
    map<Date, double> budget;
    int q, value;
    string command, date_from, date_to;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> command;
        if (command == "ComputeIncome") {
            cin >> date_from >> date_to;
            cout << ComputeIncome(budget, ConvertStringToDate(date_from), ConvertStringToDate(date_to)) << endl;
        }
        else if (command == "Earn") {
            cin >> date_from >> date_to;
            cin >> value;
            Earn(budget, ConvertStringToDate(date_from), ConvertStringToDate(date_to), value);
        }
    }
    return 0;
}

