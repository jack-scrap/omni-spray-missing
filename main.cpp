#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

int main() {
	Disp disp("asdf", 800, 600);

	// data
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// position
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vtc[] = {
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

	// matrix
	glm::mat4 model = glm::mat4(1.0);

	// shader
	Prog prog("shad", "shad");

	/// attribute
	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	/// uniform
	GLint uniModel = glGetUniformLocation(prog._id, "model");

	// initialize
	prog.use();

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		disp.update();
	}
}
