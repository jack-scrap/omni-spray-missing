#version 400

in vec3 pos;

uniform mat4 model;

out vec3 _pos;

void main() {
	gl_Position = model * vec4(pos, 1.0);

	_pos = pos;
}
