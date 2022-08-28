#version 400

in vec3 pos;

uniform mat4 model;

const float margin = 0.16;

vec2 res = vec2(100, 100);

const float scaleFac = 0.8;

float aspect = res.x / res.y;

void main() {
	vec2 margined = vec2(pos.x * scaleFac, pos.y * scaleFac) + vec2(vec2(margin * 2) * vec2(1, -1));

	gl_Position = model * vec4(vec2(margined.x / aspect, margined.y) + vec2(-1.0, 1.0), 0.0, 1.0);
}
