#version 330

in vec3 normal;
in vec3 light;

out vec4 color;

void main() {
   //color = vec4(1.0,1.0,1.0,1.0);
   color = vec4(0.0,0.2,0.0,0.0)+vec4(vec3(0.0,1.0,0.0)*clamp(dot(normal,-light),0,1),1.0);
}
