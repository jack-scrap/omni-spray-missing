#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "glyph.h"

Glyph::Glyph(char c, unsigned int i) :
	_prog("shad", "shad") {
		std::string name = util::glyphName(c);

		// data
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// position
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		std::vector<GLfloat> vtc = util::rdAttr(name, 0);
		glBufferData(GL_ARRAY_BUFFER, vtc.size() * sizeof (GLfloat), &vtc[0], GL_STATIC_DRAW);

		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		std::vector<GLushort> idc = util::rdIdc(name, 0);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, idc.size() * sizeof (GLushort), &idc[0], GL_STATIC_DRAW);

		_noIdc = idc.size();

		// matrix
		_model = glm::mat4(1.0);
		_model = glm::translate(_model, glm::vec3(i * 0.5, 0.0, 0.0));

		_prog.use();

		/// attribute
		GLint attrPos = glGetAttribLocation(_prog._id, "pos");
		glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
		glEnableVertexAttribArray(attrPos);

		/// uniform
		_uniModel = glGetUniformLocation(_prog._id, "model");

		glUniformMatrix4fv(_uniModel, 1, GL_FALSE, glm::value_ptr(_model));

		_prog.unUse();
	}

void Glyph::draw() {
	_prog.use();

	glDrawElements(GL_TRIANGLES, _noIdc, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	_prog.unUse();
}
