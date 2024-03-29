// Author : Maks Mishin
// Date : 2/8/2022.

#pragma once

#include <vector>
#include <string>
#include <map>
#include "responses.h"

class BusManager {
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops);

    BusesForStopResponse GetBusesForStop(const std::string& stop) const;

    StopsForBusResponse GetStopsForBus(const std::string& bus) const;

    AllBusesResponse GetAllBuses() const;

private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
};
