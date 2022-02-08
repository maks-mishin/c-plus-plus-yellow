// Author : Maks Mishin
// Date : 2/8/2022

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream input_stream(international_number);
    char sign = input_stream.get();

    getline(input_stream, country_code_, '-');
    getline(input_stream, city_code_, '-');
    getline(input_stream, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Phone number '" + international_number + "' is incorrect.");
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
