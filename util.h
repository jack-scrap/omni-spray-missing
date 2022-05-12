#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

namespace util {
	template <typename T>
	T rd(std::string fName);

	template <>
	std::string rd(std::string name);

	template <>
	std::vector<std::string> rd(std::string fName);

	std::vector<std::string> split(std::string buff, char delim);

	std::vector<GLfloat> rdAttr(std::string fName, unsigned int attr);

	std::vector<GLushort> rdIdc(std::string fName, unsigned int attr);
}
