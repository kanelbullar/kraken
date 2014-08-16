#version 330

layout(points) in;
layout(triangle_strip,max_vertices = 102) out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightpos;
uniform ivec3 dim;
uniform sampler3D vf;

out vec3 normal;
out vec3 light;

// find any orthogonal vector
vec3 orthogonal(vec3 n) {

   vec3 p;

   // n isn't collinear to (1.0,0.0,0.0)
   if(n.y != 0.0 || n.z != 0.0) {

      p = cross(n,vec3(1.0,0.0,0.0));
   }

   else {

      p = vec3(0.0,n.x,0.0);
   }

   return p;
}

void main() {

   const float PI_2     = 6.28318530718,
               RADIUS   = 0.2;
   const int   SEGMENTS = 17;


   mat4 perspective_view = projection * view;

   // particle, vertex_position, texture_position
   vec3 p_pos = gl_in[0].gl_Position.xyz,
        v_pos = vec3(0.0),
        t_pos = p_pos;
   
   t_pos[0] = (t_pos[0] + dim[0] / 2) / dim[0];
   t_pos[1] = (t_pos[1] + dim[1] / 2) / dim[1];
   t_pos[2] = (t_pos[2] + dim[2] / 2) / dim[2];

   vec3 n = texture(vf,t_pos).rgb;

   if(length(n) == 0) {
      n = normalize(vec3(-1.0,0.0,0.0));
   }

   vec3 u = normalize(orthogonal(n)) * RADIUS,
        v = normalize(cross(n,u))    * RADIUS;   

   vec3 pos_mantle[2] , light_mantle[2];

   float rad_increment = PI_2 / SEGMENTS;

   for(float rad = 0.0 ; rad < PI_2 ; rad += rad_increment) {

      // begin : mantle triangle
      v_pos  = p_pos + cos(rad) * u + sin(rad) * v;
      normal = normalize(v_pos - p_pos);
      light  = normalize(v_pos - lightpos);
      gl_Position = perspective_view * vec4(v_pos,1.0);
      EmitVertex();
      pos_mantle[0]   = v_pos;
      light_mantle[0] = light;
      
      v_pos   = p_pos + cos(rad+rad_increment) * u + sin(rad+rad_increment) * v;
      normal  = normalize(v_pos - p_pos);
      light   = normalize(v_pos - lightpos);
      gl_Position = perspective_view * vec4(v_pos,1.0);
      EmitVertex();
      pos_mantle[1]   = v_pos;
      light_mantle[1] = light;

      v_pos   = p_pos + n;
      normal  = normalize(v_pos - p_pos);
      light   = normalize(v_pos - lightpos);
      gl_Position = perspective_view * vec4(v_pos,1.0);
      EmitVertex();
      EndPrimitive();
      // end : mantle triangle


      // begin : base triangle
      normal = -n;
      light  = light_mantle[0];
      gl_Position = perspective_view * vec4(pos_mantle[0],1.0);
      EmitVertex();

      normal = -n;
      light = light_mantle[1];
      gl_Position = perspective_view * vec4(pos_mantle[1],1.0);
      EmitVertex();

      normal = -n;
      light  = p_pos - lightpos;
      gl_Position = perspective_view * vec4(p_pos,1.0);
      EmitVertex();
      EndPrimitive();
      // end : base triangle
   }
   

}
