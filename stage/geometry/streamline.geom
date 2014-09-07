#version 440

#define base_number 10

layout (points) in;
layout (line_strip,max_vertices = base_number) out;

uniform mat4 perspective_view;
uniform ivec3 dim;
uniform vec2 interval;
uniform sampler3D vf;
uniform sampler1D tf;

out vec4 color;

vec4 transfer(float absolute) {

   vec3 c_min = vec3(0.0,0.0,1.0),
        c_max = vec3(1.0,0.0,0.0);

   float range = interval[1] - interval[0];

   float normalized_length = (absolute - interval[0]) / range;

   //if(normalized_length > 0.0 && normalized_length < 1.0)

      //return vec4(0.0,1.0,0.0,1.0);

   return  texture(tf,clamp(normalized_length,0.0,1.0)).rgba;
}

vec3 convert(vec3 particle_pos) {

   vec3 texture_pos;

   texture_pos[0] = (particle_pos[0] + float(dim[0]) / 2) / dim[0];
   texture_pos[1] = (particle_pos[1] + float(dim[1]) / 2) / dim[1];
   texture_pos[2] = (particle_pos[2] + float(dim[2]) / 2) / dim[2];

   return texture_pos;
}

vec3 runge_kutta(vec3 particle_pos) {

   vec3 texture_pos;

   vec3 x0 = particle_pos;
   texture_pos = convert(x0);
   vec3 v0 = texture(vf,texture_pos).rgb;

   vec3 x1 = x0 + 0.5 * v0;
   texture_pos = convert(x1);
   vec3 v1 = texture(vf,texture_pos).rgb;

   vec3 x2 = x1 + 0.5 * v1;
   texture_pos = convert(x2);
   vec3 v2 = texture(vf,texture_pos).rgb;

   vec3 x3 = x2 + v2;
   texture_pos = convert(x3);
   vec3 v3 = texture(vf,texture_pos).rgb;

   return (1.0/6.0) * (v0 + 2*v1 + 2*v2 + v3);
}

void main () {

   vec3 p_pos = gl_in[0].gl_Position.xyz;
   vec3 n;   

   for(int i = 0; i <= base_number; ++i) {
     
      n = runge_kutta(p_pos);

      if(length(n) == 0) break;

      p_pos += n;
      
      vec4 geom_color = transfer(length(n));

      //if(geom_color.a==1) geom_color = vec4(1.0,1.0,1.0,1.0); 
      color = geom_color;
      gl_Position = perspective_view * vec4(p_pos,1.0);
      EmitVertex();
   }

   EndPrimitive();
}
