#version 400

in vec2 _pos;

vec3[2] col = vec3[2](
	vec3(38, 38, 38),
	vec3(255, 142, 65)
);

void main() {
	gl_FragColor = vec4(col[int(mod(_pos.x, 1.0 * 2) > 1.0 ^^ mod(_pos.y, 1.0 * 2) > 1.0)] / 225.0, 1.0);
}
