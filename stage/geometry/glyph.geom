#version 330

layout(points) in;
layout(triangle_strip,max_vertices = 78) out;

// tranformation
uniform mat4 perspective_view;

// light
uniform vec3 lightpos;

// vector field
uniform vec2 interval;
uniform ivec3 dim;
uniform sampler3D vf;

// shading
out vec3 normal;
out vec3 light;
out vec3 color;


// find orthogonal plane vector
vec3 orthogonal(vec3 n) {

   vec3 o;

   // n isn't collinear to (1.0,0.0,0.0)
   if(n.y != 0.0 || n.z != 0.0) {

      o = cross(n,vec3(1.0,0.0,0.0));
   }

   else {

      o = vec3(0.0,n.x,0.0);
   }

   return o;
}

// calc normal for the mantle geometry
vec3 mantle_normal(vec3 pos) {

   vec4 mn = vec4(pos - gl_in[0].gl_Position.xyz,0.0);

   //mn = dir_tranform * mn;

   return normalize(mn.xyz);
}

// calc normal for the base geometry
vec3 base_normal(vec3 n) {

   vec4 bn = vec4(-n,0.0);

   //bn = dir_tranform * bn;

   return normalize(bn.xyz);
}

// calc normalized vector from lightsource to surface position
vec3 surface_light(vec3 pos) {

   vec4 l = vec4(pos - lightpos,0.0);

   //l = dir_tranform * l;

   return normalize(l.xyz);
}

// map normal length to color
vec3 transfer(float absolute) {
   
   vec3 c_min = vec3(0.0,0.0,1.0),
        c_max = vec3(1.0,0.0,0.0);

   float weight = (absolute - interval[0]) / (interval[1] - interval[0]);

   return  (1.0 - weight) * c_min + weight * c_max;
}


void main() {

   const float PI_2     = 6.28318530718,
               RADIUS   = 0.2;
   const int   SEGMENTS = 13;

   // particle, vertex_position, texture_position
   vec3 p_pos = gl_in[0].gl_Position.xyz,
        v_pos = vec3(0.0),
        t_pos = p_pos;
   
   t_pos[0] = (t_pos[0] + dim[0] / 2) / dim[0];
   t_pos[1] = (t_pos[1] + dim[1] / 2) / dim[1];
   t_pos[2] = (t_pos[2] + dim[2] / 2) / dim[2];

   vec3 n = texture(vf,t_pos).rgb;

   if(length(n) != 0.0) {

      vec3 geom_color = transfer(length(n)); 
      n = normalize(n);

      p_pos -= n/2;

      vec3 u = normalize(orthogonal(n)) * RADIUS,
           v = normalize(cross(n,u))    * RADIUS;   

      vec3 pos_mantle[2] , light_mantle[2];

      float rad_increment = PI_2 / SEGMENTS;

      for(float rad = 0.0 ; rad < PI_2 ; rad += rad_increment) {

         // begin : mantle triangle
         v_pos  = p_pos + cos(rad) * u + sin(rad) * v;
         normal = mantle_normal(v_pos);
         light  = surface_light(v_pos);
         color  = geom_color;

         pos_mantle[0]   = v_pos;
         light_mantle[0] = light;

         gl_Position = perspective_view * vec4(v_pos,1.0);
         EmitVertex();

      
         v_pos  = p_pos + cos(rad+rad_increment) * u 
                         + sin(rad+rad_increment) * v;
         normal = mantle_normal(v_pos);
         light  = surface_light(v_pos);
         color  = geom_color;

         pos_mantle[1]   = v_pos;
         light_mantle[1] = light;

         gl_Position = perspective_view * vec4(v_pos,1.0);
         EmitVertex();


         v_pos  = p_pos + n;
         normal = mantle_normal(v_pos);
         light  = surface_light(v_pos);
         color  = geom_color;

         gl_Position = perspective_view * vec4(v_pos,1.0);
         EmitVertex();

         EndPrimitive();
         // end : mantle triangle


         // begin : base triangle

         vec3 bn = base_normal(n);

         normal = bn;
         light  = light_mantle[0];
         color  = geom_color;

         gl_Position = perspective_view * vec4(pos_mantle[0],1.0);
         EmitVertex();

         normal = bn;
         light  = light_mantle[1];
         color  = geom_color;

         gl_Position = perspective_view * vec4(pos_mantle[1],1.0);
         EmitVertex();

         normal = bn;
         light  = surface_light(p_pos);
         color  = geom_color;

         gl_Position = perspective_view * vec4(p_pos,1.0);
         EmitVertex();

         EndPrimitive();
         // end : base triangle
      }
   }
}
