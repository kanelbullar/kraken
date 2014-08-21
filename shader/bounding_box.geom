#version 330

layout(points) in;
layout(line_strip,max_vertices = 20) out;

uniform mat4  projection;
uniform mat4  view;
uniform ivec3 dim;

void main() {

   mat4 perspective_view = projection * view;

   vec3 p_pos = gl_in[0].gl_Position.xyz;
   
   float plane[6];

   plane[0] = p_pos[0] - dim[0] / 2;
   plane[1] = p_pos[0] + dim[0] / 2;
   plane[2] = p_pos[1] - dim[1] / 2;
   plane[3] = p_pos[1] + dim[1] / 2;
   plane[4] = p_pos[2] - dim[2] / 2;
   plane[5] = p_pos[2] + dim[2] / 2;

   vec4 corner[8];

   corner[0] = perspective_view * vec4(plane[0],plane[2],plane[4],1.0);
   corner[1] = perspective_view * vec4(plane[1],plane[2],plane[4],1.0);
   corner[2] = perspective_view * vec4(plane[0],plane[3],plane[4],1.0);
   corner[3] = perspective_view * vec4(plane[1],plane[3],plane[4],1.0);
   corner[4] = perspective_view * vec4(plane[0],plane[2],plane[5],1.0);
   corner[5] = perspective_view * vec4(plane[1],plane[2],plane[5],1.0);
   corner[6] = perspective_view * vec4(plane[0],plane[3],plane[5],1.0);
   corner[7] = perspective_view * vec4(plane[1],plane[3],plane[5],1.0);

   gl_Position = corner[0];
   EmitVertex();
   gl_Position = corner[1];
   EmitVertex();
   gl_Position = corner[3];
   EmitVertex();
   gl_Position = corner[2];
   EmitVertex();
   gl_Position = corner[0];
   EmitVertex();
   EndPrimitive();

   gl_Position = corner[4];
   EmitVertex();
   gl_Position = corner[5];
   EmitVertex();
   gl_Position = corner[7];
   EmitVertex();
   gl_Position = corner[6];
   EmitVertex();
   gl_Position = corner[4];
   EmitVertex();
   EndPrimitive();

   for(int index = 0 ; index < 4 ; ++index) {

      gl_Position = corner[index];
      EmitVertex();
      gl_Position = corner[index+4];
      EmitVertex();
      EndPrimitive();
   }
}
