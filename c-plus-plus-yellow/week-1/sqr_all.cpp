#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

/*
	Template function for vector
*/
template <class T>
vector<T> Sqr(vector<T>& src_vec);

/*
	For pair
*/
template <class Key, class Value>
pair<Key, Value> Sqr(pair<Key, Value>& src_pair);

/*
	For map
*/
template <class Key, class Value>
map<Key, Value> Sqr(map<Key, Value>& src_map);

/*
	For simple types
*/
template <class T>
T Sqr(T value)
{
	return value * value;
}

template <class T>
vector<T> Sqr(vector<T>& src_vec)
{
	vector<T> result;
	for (const T& item : src_vec)
	{
		result.push_back(Sqr(item));
	}

	return result;
}

template <class Key, class Value>
pair<Key, Value> Sqr(const pair<Key, Value>& src_pair)
{
	pair<Key, Value> result = {
		Sqr(src_pair.first), Sqr(src_pair.second)
	};
	
	return result;
}


template <class Key, class Value>
map<Key, Value> Sqr(map<Key, Value>& src_map)
{
	map<Key, Value> result;

	for (const auto item : src_map)
	{
		auto key = item.first;
		auto value = item.second;

		result[key] = Sqr(value);
	}

	return result;
}
