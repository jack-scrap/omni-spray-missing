#version 400

in vec3 _pos;
out vec4 col;

void main() {
	col = vec4(_pos, 1.0);
}
