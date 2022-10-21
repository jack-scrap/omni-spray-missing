#version 400

in vec2 pos;

out vec2 _pos;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);

	_pos = pos * vec2(1, -1);
}
