#pragma once

#include <vector>
#include <string>

namespace util {
	template <typename T>
	T rd(std::string fName);

	template <>
	std::string rd(std::string name);

	template <>
	std::vector<std::string> rd(std::string fName);

	std::vector<std::string> split(std::string buff, char delim);
}
