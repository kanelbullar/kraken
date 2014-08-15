#version 330

layout(points) in;
layout(triangle_strip,max_vertices=18) out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightpos;

out vec3 normal;
out vec3 light;
out vec3 color;

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


   vec3 n = normalize(vec3(0.0,0.0,-1.0));
   vec3 u = normalize(orthogonal(n));
   vec3 v = normalize(cross(n,u));

   vec3 points[5], normals[5];

   points[0] = gl_in[0].gl_Position.xyz + n;
   points[1] = gl_in[0].gl_Position.xyz + u;
   points[2] = gl_in[0].gl_Position.xyz - v;
   points[3] = gl_in[0].gl_Position.xyz - u;
   points[4] = gl_in[0].gl_Position.xyz + v;

   normals[0] = normalize(cross(points[1]-points[0],points[2]-points[0]));
   normals[1] = normalize(cross(points[2]-points[0],points[3]-points[0]));
   normals[2] = normalize(cross(points[3]-points[0],points[4]-points[0]));
   normals[3] = normalize(cross(points[4]-points[0],points[1]-points[0]));
   normals[4] = normalize(cross(points[4]-points[1],points[2]-points[1]));

   /*// 012 Front
   gl_Position = projection * view * vec4(points[0],1.0);
   normal = normals[0];
   light = normalize(lightpos - points[0]);
   color = vec3(1.0,0.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   normal = normals[0];
   light = normalize(lightpos - points[1]);
   color = vec3(1.0,0.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[2],1.0);
   normal = normals[0];
   light = normalize(lightpos - points[2]);
   color = vec3(1.0,0.0,0.0);
   EmitVertex();
   EndPrimitive();

   // 230 Right
   gl_Position = projection * view * vec4(points[2],1.0);
   normal = normals[1];
   light = normalize(lightpos - points[2]);
   color = vec3(0.0,0.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   normal = normals[1];
   light = normalize(lightpos - points[3]);
   color = vec3(0.0,0.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[0],1.0);
   normal = normals[1];
   light = normalize(lightpos - points[0]);
   color = vec3(0.0,0.0,1.0);
   EmitVertex();
   EndPrimitive();*/

   // 304 Back
   gl_Position = projection * view * vec4(points[3],1.0);
   normal = normals[2];
   light = normalize(lightpos - points[3]);
   color = vec3(0.0,1.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[0],1.0);
   normal = normals[2];
   light = normalize(lightpos - points[0]);
   color = vec3(0.0,1.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[4],1.0);
   normal = normals[2];
   light = normalize(lightpos - points[4]);
   color = vec3(0.0,1.0,0.0);
   EmitVertex();
   EndPrimitive();

   /*// 041 Left
   gl_Position = projection * view * vec4(points[0],1.0);
   normal = normals[3];
   light = normalize(lightpos - points[0]);
   color = vec3(0.0,1.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[4],1.0);
   normal = normals[3];
   light = normalize(lightpos - points[4]);
   color = vec3(0.0,1.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   normal = normals[3];
   light = normalize(lightpos - points[1]);
   color = vec3(0.0,1.0,1.0);
   EmitVertex();
   EndPrimitive();

   // 413 Down Left
   gl_Position = projection * view * vec4(points[4],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[4]);
   color = vec3(1.0,0.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[1],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[1]);
   color = vec3(1.0,0.0,1.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[3]);
   color = vec3(1.0,0.0,1.0);
   EmitVertex();
   EndPrimitive();

   // 123 Down Right
   gl_Position = projection * view * vec4(points[1],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[1]);
   color = vec3(1.0,1.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[2],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[2]);
   color = vec3(1.0,1.0,0.0);
   EmitVertex();
   gl_Position = projection * view * vec4(points[3],1.0);
   normal = normals[4];
   light = normalize(lightpos - points[3]);
   color = vec3(1.0,1.0,0.0);
   EmitVertex();
   EndPrimitive();*/
}
