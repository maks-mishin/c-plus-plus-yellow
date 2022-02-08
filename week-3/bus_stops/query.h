// Author : Maks Mishin
// Date : 2/8/2022.

#pragma once

#include <string>
#include <iostream>
#include <vector>

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);