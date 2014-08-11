#version 330

layout(triangles) in;
layout(triangle_strip,max_vertices = 3) out;

void main() {

   for(int index = 0 ; index < 3 ; ++index) {

      gl_Position = gl_in[index].gl_Position;
      EmitVertex();
   }

   EndPrimitive();
}
