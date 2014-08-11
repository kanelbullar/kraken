#version 330

layout(points) in;
layout(triangle_strip,max_vertices=100) out;

uniform mat4 projection;
uniform mat4 view;

vec3 orthogonal(vec3 n) {

   vec3 p;

   if(n.y != 0.0 || n.z != 0.0) {

      p = cross(n,vec3(1.0,0.0,0.0));
   }

   else {

      p = vec3(0.0,n.x,0.0);
   }

   return p;
}

void main() {

   vec3 n = vec3(0.0,1.0,0.0);
   vec3 u = vec3(-1.0,0.0,1.0);
   //vec3 u = normalize(orthogonal(n));
   vec3 v = cross(n,u);

   vec3 points[5];

/*   points[0] = vec3(0,1,0);
   points[1] = vec3(-1,0,1);
   points[2] = vec3(1,0,1);
   points[3] = vec3(1,0,-1);
   points[4] = vec3(-1,0,-1);*/

   points[0] = gl_in[0].gl_Position.xyz + n;
   points[1] = gl_in[0].gl_Position.xyz + u;
   points[2] = gl_in[0].gl_Position.xyz - v;
   points[3] = gl_in[0].gl_Position.xyz - u;
   points[4] = gl_in[0].gl_Position.xyz + v;

   /*gl_Position = projection * view * vec4(points[0],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[2],1.0);
   EmitVertex();
   EndPrimitive();*/

/*   gl_Position = projection * view * vec4(points[2],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[0],1.0);
   EmitVertex();
   EndPrimitive();*/

/*   gl_Position = projection * view * vec4(points[1],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[2],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   EmitVertex();
   EndPrimitive();*/

   gl_Position = projection * view * vec4(points[0],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[2],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[0],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[4],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   EmitVertex();
   EndPrimitive();
}
