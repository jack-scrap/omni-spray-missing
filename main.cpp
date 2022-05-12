#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <png.h>

#include "disp.h"
#include "prog.h"
#include "util.h"

static constexpr glm::vec3 col[2] = {
	glm::vec3(38, 38, 38),
	glm::vec3(255, 142, 65)
};

const GLfloat margin = 0.16;

enum Constants { SCREENSHOT_MAX_FILENAME = 256 };
static GLubyte *pixels = NULL;
static GLuint fbo;
static GLuint rbo_color;
static GLuint rbo_depth;
static int offscreen = 1;
static unsigned int max_nframes = 128;
static unsigned int nframes = 0;
static unsigned int time0;
static unsigned int height = 128;
static unsigned int width = 128;
#define PPM_BIT (1 << 0)
#define LIBPNG_BIT (1 << 1)
#define FFMPEG_BIT (1 << 2)
static unsigned int output_formats = PPM_BIT | LIBPNG_BIT | FFMPEG_BIT;

std::vector<std::string> split(std::string buff, char delim) {
	std::vector<std::string> tok;

	std::stringstream s(buff);
	std::string seg;
	while (std::getline(s, seg, delim)) {
		tok.push_back(seg);
	}

	return tok;
}

std::vector<std::string> rd(std::string fName) {
	std::ifstream in;
	in.open(fName);

	std::vector<std::string> cont;

	for (std::string l; std::getline(in, l);) {
		cont.push_back(l);
	}

	in.close();

	return cont;
}

std::vector<GLfloat> rdAttr(std::string fName, unsigned int attr) {
	std::vector<GLfloat> _;

	std::vector<std::string> buff = rd(fName + ".obj");

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
		std::vector<std::string> tok = split(buff[l], ' ');

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

std::vector<GLushort> rdIdc(std::string fName, unsigned int attr) {
	std::vector<GLushort> _;

	std::vector<std::string> buff = rd(fName + ".obj");

	for (int l = 0; l < buff.size(); l++) {
		std::vector<std::string> tok = split(buff[l], ' ');

		if (tok[0] == "f") {
			for (int i = 1; i < 1 + 3; i++) {
				std::vector<std::string> type = split(tok[i], '/');

				_.push_back(std::stoi(type[attr]) - 1);
			}
		}
	}

	return _;
}

/* Adapted from https://github.com/cirosantilli/cpp-cheat/blob/19044698f91fefa9cb75328c44f7a487d336b541/png/open_manipulate_write.c */
static png_byte *png_bytes = NULL;
static png_byte **png_rows = NULL;
static void screenshot_png(const char *filename, unsigned int width, unsigned int height, GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows) {
	size_t i, nvals;
	const size_t format_nchannels = 4;
	FILE *f = fopen(filename, "wb");
	nvals = format_nchannels * width * height;
	*pixels = (GLubyte*) realloc(*pixels, nvals * sizeof(GLubyte));
	*png_bytes = (png_byte*) realloc(*png_bytes, nvals * sizeof(png_byte));
	*png_rows = (png_byte**) realloc(*png_rows, height * sizeof(png_byte*));
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, *pixels);
	for (i = 0; i < nvals; i++)
		(*png_bytes)[i] = (*pixels)[i];
	for (i = 0; i < height; i++)
		(*png_rows)[height - i - 1] = &(*png_bytes)[i * width * format_nchannels];
	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) abort();
	png_infop info = png_create_info_struct(png);
	if (!info) abort();
	if (setjmp(png_jmpbuf(png))) abort();
	png_init_io(png, f);
	png_set_IHDR(
			png,
			info,
			width,
			height,
			8,
			PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
			);
	png_write_info(png, info);
	png_write_image(png, *png_rows);
	png_write_end(png, NULL);
	png_destroy_write_struct(&png, &info);
	fclose(f);
}

int main() {
	Disp disp("asdf", 160, 171);

	char c = 'a';

	// data
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// position
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<GLfloat> vtc = rdAttr(std::string(1, c), 0);
	glBufferData(GL_ARRAY_BUFFER, vtc.size() * sizeof (GLfloat), &vtc[0], GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	std::vector<GLushort> idc = rdIdc(std::string(1, c), 0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idc.size() * sizeof (GLushort), &idc[0], GL_STATIC_DRAW);

	// matrix
	const GLfloat scaleFac = 0.8;

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-1.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(margin * 2, -(margin * 2), 0.0));
	model = glm::scale(model, glm::vec3(scaleFac, scaleFac, scaleFac));

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

	disp.clear(col[true].r / 255.0, col[true].g / 255.0, col[true].b / 255.0, 1);

	glDrawElements(GL_TRIANGLES, idc.size(), GL_UNSIGNED_SHORT, (GLvoid*) 0);

	disp.update();

	GLubyte* pixels = NULL;
	screenshot_png(std::string(std::string(1, c) + ".png").c_str(), 160, 171, &pixels, &png_bytes, &png_rows);

	SDL_Delay(1000);
}
