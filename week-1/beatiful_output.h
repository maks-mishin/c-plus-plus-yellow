#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

/*
	@brief - Function for prepare the output of Collection (vector, map, i.e.)
	@param1 - obj Collection
	@param2 - delimiter (char)
*/
template <class Collection>
std::string Join(const Collection& c, char d)
{
	std::stringstream ss;
	bool first = true;
	for (const auto& item : c)
	{
		if (!first)
		{
			ss << d;
		}
		first = false;
		ss << item;
	}
	return ss.str();
}

template <class First, class Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p)
{
	out << '(' << p.first << ',' << p.second << ')';
	return out;
}

template <class T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi)
{
	out << '[' << Join(vi, ',') << ']';
	return out;
}

template <class Key, class Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m)
{
	out << '{' << Join(m, ',') << '}';
	return out;
}