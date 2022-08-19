#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

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

std::vector<GLfloat> util::rdAttr(std::string fName, unsigned int attr) {
	std::vector<GLfloat> _;

	std::vector<std::string> buff = util::rd<std::vector<std::string>>("res/" + fName + ".obj");

	const std::string id[3] = {
		"v",
		"vt",
		"vn"
	};
	const unsigned int sz[3] = {
		3,
		2,
		3
	};

	for (int l = 0; l < buff.size(); l++) {
		std::vector<std::string> tok = util::split(buff[l], ' ');

		if (tok[0] == id[attr]) {
			for (int i = 1; i < 1 + sz[attr]; i++) {
				std::stringstream out;
				out << std::fixed << std::setprecision(4) << std::stof(tok[i]);

				_.push_back(std::stof(out.str()));
			}
		}
	}

	return _;
}

std::vector<GLushort> util::rdIdc(std::string fName, unsigned int attr) {
	std::vector<GLushort> _;

	std::vector<std::string> buff = util::rd<std::vector<std::string>>("res/" + fName + ".obj");

	for (int l = 0; l < buff.size(); l++) {
		std::vector<std::string> tok = util::split(buff[l], ' ');

		if (tok[0] == "f") {
			for (int i = 1; i < 1 + 3; i++) {
				std::vector<std::string> type = util::split(tok[i], '/');

				_.push_back(std::stoi(type[attr]) - 1);
			}
		}
	}

	return _;
}

std::string util::glyphName(char c) {
	std::string name;

	// alpha-numeric
	if (
		(c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z')
	) {
		name = std::string(1, c);
	} else {
		switch (c) {
			case ' ':
				name = "spc";

				break;

			case '!':
				name = "bang";

				break;

			case '"':
				name = "dbl_quote";

				break;

			case '#':
				name = "pound";

				break;

			case '$':
				name = "dollar";

				break;

			case '%':
				name = "percent";

				break;

			case '&':
				name = "ampersand";

				break;

			case '\'':
				name = "single_quote";

				break;

			case '(':
				name = "round_bracket_l";

				break;

			case ')':
				name = "round_bracket_r";

				break;

			case '*':
				name = "asterisk";

				break;

			case '+':
				name = "plus";

				break;

			case ',':
				name = "comma";

				break;

			case '-':
				name = "minus";

				break;

			case '.':
				name = "period";

				break;

			case '/':
				name = "fwd_slash";

				break;

			case ':':
				name = "colon";

				break;

			case ';':
				name = "semi_colon";

				break;

			case '<':
				name = "less_than";

				break;

			case '=':
				name = "equals";

				break;

			case '>':
				name = "greater_than";

				break;

			case '?':
				name = "question";

				break;

			case '@':
				name = "at";

				break;

			case '[':
				name = "sq_bracket_l";

				break;

			case ']':
				name = "sq_bracket_r";

				break;

			case '^':
				name = "carat";

				break;

			case '_':
				name = "underscore";

				break;

			case '`':
				name = "back_tick";

				break;

			case '{':
				name = "curly_bracket_l";

				break;

			case '|':
				name = "pipe";

				break;

			case '}':
				name = "curly_bracket_r";

				break;

			case '~':
				name = "tilde";

				break;
		}
	}

	return name;
}
