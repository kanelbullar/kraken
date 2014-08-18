#version 330

in vec3 normal;
in vec3 light;
in vec3 color;

out vec4 frag_color;

void main() {

   vec3 phong_color = 0.2 * color + clamp(dot(normal,light),0.0,1.0) * color;

   frag_color = vec4(phong_color,1.0);
}
