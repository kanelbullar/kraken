#version 330

in vec3 triangle_color;
in vec3 normal;
in vec3 light;
in vec3 color;


out vec4 frag_color;

void main() {
   //color = vec4(1.0,1.0,1.0,1.0);
   frag_color = vec4(0.2*color,1.0)
             + vec4(color*clamp(dot(normal,-light),0,1),1.0);
   //color = vec4(triangle_color,1.0);
}
