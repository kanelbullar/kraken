#version 330

in vec3 normal;
in vec3 light;
in vec3 in_color;

out vec4 color;

void main() {
   //color = vec4(1.0,1.0,1.0,1.0);
   color = vec4((0.2*in_color),1.0)
         + vec4(in_color*clamp(dot(normal,-light),0,1),1.0);
}
