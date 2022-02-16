// Author : Maks Mishin
// Date 2/16/2022.
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

class Date {
public:
    static Date ConvertStringToDate(const string& date_string) {
        auto it_year = find(begin(date_string), end(date_string), '-');
        int year = stoi(string(begin(date_string), it_year));

        auto it_month = find(it_year+1, end(date_string), '-');
        int month = stoi(string(it_year+1, it_month));

        int day = stoi(string(it_month+1, end(date_string)));
        return {year, month, day};
    }

    time_t AsTimestamp() const {
        tm t;
        t.tm_sec  = 0;
        t.tm_min  = 0;
        t.tm_hour = 0;
        t.tm_mday = day_;
        t.tm_mon  = month_ - 1;
        t.tm_year = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    Date& operator++();
private:
    int year_;
    int month_;
    int day_;

    Date(int year, int month, int day)
            : year_(year), month_(month), day_(day) {}
};

// returns difference between two dates in days
auto DiffDates(const Date& date_from, const Date& date_to) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return difftime(timestamp_to, timestamp_from) / SECONDS_IN_DAY;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return tie(lhs.year_, lhs.month_, lhs.day_) < tie(rhs.year_, rhs.month_, rhs.day_);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return tie(lhs.year_, lhs.month_, lhs.day_) == tie(rhs.year_, rhs.month_, rhs.day_);
}

bool IsLeapYear(int year) {
    return year % 4 == 0 and year % 100 != 0 or year % 400 == 0;
}

Date &Date::operator++() {
    vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeapYear(year_))
        days[1] = 29;

    int days_month = days[month_ - 1];

    if (day_ < days_month) {
        day_++;
    }
    else {
        day_ = 1;

        if( month_ < 12 ) {
            month_++;
        }
        else {
            month_ = 1;
            year_++;
        }
    }
    return *this;
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

void Earn(map<Date, double>& budget, const Date& date_from, const Date& date_to, int value) {
    if (date_to < date_from) {
        throw invalid_argument("argument 'date_to' should be great of 'date_from'");
    }
    Date tempDate = date_from;

    auto count_days = DiffDates(date_from, date_to) + 1; // разница между датами в днях
    auto part_value = value / count_days;

    for(int i = 0; i < count_days; i++) {
        if (budget.count(tempDate) > 0) {
            budget[tempDate] += part_value;
        }
        else {
            budget[tempDate] = part_value;
        }
        ++tempDate;
    }
}

void TestAuthor() {
    map<Date, double> budget;
    double income;
    Earn(budget, Date::ConvertStringToDate("2000-01-02"),
            Date::ConvertStringToDate("2000-01-06"), 20);
    income = ComputeIncome(budget, Date::ConvertStringToDate("2000-01-01"),
                           Date::ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 20, "author test income 20");

    income = ComputeIncome(budget, Date::ConvertStringToDate("2000-01-01"),
                           Date::ConvertStringToDate("2000-01-03"));
    AssertEqual(income, 8, "author test income 8");

    Earn(budget, Date::ConvertStringToDate("2000-01-03"),
         Date::ConvertStringToDate("2000-01-03"), 10);
    income = ComputeIncome(budget, Date::ConvertStringToDate("2000-01-01"),
                           Date::ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 30, "author test income 30");
}

void TestFirst() {
    map<Date, double> budget;
    double income;
//    test zero income
    Earn(budget, Date::ConvertStringToDate("2000-01-01"),
            Date::ConvertStringToDate("2000-01-01"), 0);
    income = ComputeIncome(budget, Date::ConvertStringToDate("2000-01-01"),
                           Date::ConvertStringToDate("2001-01-01"));
    AssertEqual(income, 0, "first test income 0");

//    test income for several months
    Earn(budget, Date::ConvertStringToDate("2000-01-17"),
         Date::ConvertStringToDate("2000-02-01"), 900);
    income = ComputeIncome(budget, Date::ConvertStringToDate("2000-01-17"),
                           Date::ConvertStringToDate("2000-02-01"));
    AssertEqual(income, 900, "first test income 900");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestAuthor, "TestAuthor");
    runner.RunTest(TestFirst, "TestFirst");

    cout.precision(25);
    map<Date, double> budget;
    int q, value;
    string command, date_from, date_to;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> command;
        if (command == "ComputeIncome") {
            cin >> date_from >> date_to;
            cout << ComputeIncome(budget, Date::ConvertStringToDate(date_from),
                                  Date::ConvertStringToDate(date_to)) << endl;
        }
        else if (command == "Earn") {
            cin >> date_from >> date_to;
            cin >> value;
            Earn(budget, Date::ConvertStringToDate(date_from),
                 Date::ConvertStringToDate(date_to), value);
        }
    }
    return 0;
}