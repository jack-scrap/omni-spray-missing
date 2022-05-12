#include <fstream>
#include <iostream>
#include <sstream>

#include "util.h"

template <typename T>
T util::rd(std::string fName) {
}

template <>
std::string util::rd<std::string>(std::string name) {
	std::ifstream in;
	in.open("./" + name);

	std::string total;
	for (std::string l; std::getline(in, l);) {
		total += l + "\n";
	}

	in.close();

	return total;
}

template <>
std::vector<std::string> util::rd(std::string fName) {
	std::ifstream in;
	in.open(fName);

	std::vector<std::string> cont;

	for (std::string l; std::getline(in, l);) {
		cont.push_back(l);
	}

	in.close();

	return cont;
}

std::vector<std::string> util::split(std::string buff, char delim) {
	std::vector<std::string> tok;

	std::stringstream s(buff);
	std::string seg;
	while (std::getline(s, seg, delim)) {
		tok.push_back(seg);
	}

	return tok;
}
