#include <iostream>
#include <vector>

void PrintAvgDays(int _amount_days)
{
	int temp_on_day;
	long long int sum = 0,
		average_temp = 0;

	std::vector<int> temp;
	std::vector<size_t> nums_days_avg;

	std::cin >> _amount_days;

	if (_amount_days > 0)
	{
		for (int i = 0; i < _amount_days; i++)
		{
			std::cin >> temp_on_day;
			temp.push_back(temp_on_day);
			sum += temp_on_day;
		}
		average_temp = sum / _amount_days;

		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] > average_temp)
				nums_days_avg.push_back(i);
		}

		std::cout << nums_days_avg.size() << std::endl;
		for (auto num_day : nums_days_avg)
		{
			std::cout << num_day << " ";
		}
	}
}