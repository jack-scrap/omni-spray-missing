#version 400

in vec3 _pos;

const float stride = 1.0;

vec3[2] col = vec3[2](
	vec3(38, 38, 38),
	vec3(255, 142, 65)
);

void main() {
	gl_FragColor = vec4(col[int(mod(_pos.x, stride * 2) > stride ^^ mod(_pos.y, stride * 2) > stride)] / 225.0, 1.0);
}
