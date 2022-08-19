#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "prog.h"

class Glyph {
	private:
		unsigned int _noIdc;

		glm::mat4 _model;

		Prog _prog;

		GLuint _uniModel;

	public:
		Glyph(char c);

		void draw();
};
