#version 330

#define PI 3.141592653
#define SEGMENTS 17

layout(points) in;
layout(triangle_strip,max_vertices=102) out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightpos;

out vec3 triangle_color;
out vec3 normal;
out vec3 light;

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

   //vec3 n = normalize(vec3(0.0,0.0,-1.0));
   vec3 n = normalize(vec3(0.7,0.3,-1.0));
   vec3 u = normalize(orthogonal(n))*0.2;
   vec3 v = normalize(cross(n,u))*0.2;

   vec3 position_mantle[2];
   vec3 light_mantle[2];

   float rad_increment = 2*PI/SEGMENTS;

   for(float rad = 0.0 ; rad < 2.0*PI; rad+=rad_increment) {
      
      vec3 position = gl_in[0].gl_Position.xyz;

      position += cos(rad+rad_increment) * u + sin(rad+rad_increment) * v;
      position_mantle[0] = position;
      normal = position - gl_in[0].gl_Position.xyz;
      light = position - lightpos;
      light_mantle[0] = light;
      gl_Position = projection * view * vec4(position,1.0);
      EmitVertex();

      position = gl_in[0].gl_Position.xyz;
      position += cos(rad) * u + sin(rad) * v;
      position_mantle[1] = position;
      normal = position - gl_in[0].gl_Position.xyz;
      light = position - lightpos;
      light_mantle[1] = light;
      gl_Position = projection * view * vec4(position,1.0);
      EmitVertex();

      position = gl_in[0].gl_Position.xyz + n;
      normal = position - gl_in[0].gl_Position.xyz;
      light = position - lightpos;
      gl_Position = projection * view * vec4(position,1.0);
      EmitVertex();
      EndPrimitive();

      normal = -n;
      light = light_mantle[1];
      gl_Position = projection * view * vec4(position_mantle[1],1.0);
      EmitVertex();

      normal = -n;
      light = light_mantle[0];
      gl_Position = projection * view * vec4(position_mantle[0],1.0);
      EmitVertex();

      gl_Position = projection * view * gl_in[0].gl_Position;
      normal = -n;
      light = gl_in[0].gl_Position.xyz - lightpos;
      EmitVertex();
      EndPrimitive();
   }
   

}
