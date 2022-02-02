#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

enum class Lang {
	DE, FR, IT
};

struct Region {
	std::string std_name;
	std::string parent_std_name;
	std::map<Lang, std::string> names;
	int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs)
{
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions)
{
	int count = 0;
	std::map<Region, int> repetition_count;
	for (const Region& region : regions)
	{
		count = std::max(count, ++repetition_count[region]);
	}
	return count;
}