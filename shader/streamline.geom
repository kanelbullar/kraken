#version 330

#define base_number 50

layout (points) in;
layout (line_strip,max_vertices = base_number) out;

uniform mat4 projection;
uniform mat4 view;
uniform ivec3 dim;
uniform vec2 interval;
uniform sampler3D vf;

out vec3 color;

vec3 transfer(float absolute) {

   vec3 c_min = vec3(0.0,0.0,1.0),
        c_max = vec3(1.0,0.0,0.0);

   float range = interval[1] - interval[0];

   float weight = (absolute - interval[0]) / range;

   return  (1.0 - weight) * c_min + weight * c_max;
}

void main () {

   const float step_width = 0.1;
   mat4 perspective_view = projection * view;

   vec3 p_pos = gl_in[0].gl_Position.xyz,
        t_pos = p_pos;

   for(int i = 0; i <= base_number; ++i) {
      
      t_pos = p_pos;
   
      t_pos[0] = (t_pos[0] + dim[0] / 2) / dim[0];
      t_pos[1] = (t_pos[1] + dim[1] / 2) / dim[1];
      t_pos[2] = (t_pos[2] + dim[2] / 2) / dim[2];

      vec3 n = texture(vf,t_pos).rgb;
      if(length(n) == 0) break;
      vec3 geom_color = transfer(length(n));
      n = normalize(n);

      n *= step_width;

      p_pos += n;
      
      color = geom_color;
      gl_Position = perspective_view * vec4(p_pos,1.0);
      EmitVertex();
   }

   EndPrimitive();
}
