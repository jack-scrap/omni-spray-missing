#version 400

vec3[2] col = vec3[2](
	vec3(38, 38, 38),
	vec3(255, 142, 65)
);

void main() {
	gl_FragColor = vec4(col[int(false)] / 255.0, 1.0);
}
