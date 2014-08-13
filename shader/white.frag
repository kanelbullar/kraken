#version 330

in vec3 normal;
in vec3 light;

out vec3 color;

void main() {

   color = vec3(1.0)*dot(normal,light);
}
