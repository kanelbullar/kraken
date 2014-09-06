#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <pipeline.hpp>
#include <vector_field.hpp>
#include <transfer_function.hpp>

#include <GL/freeglut.h>

namespace kraken {

class config {

   public :

   // callback functions

   static void display();

   static void key(unsigned char,int,int);

   static void special_key(int,int,int);

   static void time(int);

   static void resize(int,int);


   // support functions

   static void init(float);

   static void bind_field(vector_field const&);

   static void bind_transfer_function(transfer_function const&);

   static void clear();


   private :

   static void init_programs();

   static void init_uniforms();

   static void init_perspective();

   static void init_memory(std::array<unsigned short,3> const&);

   static void init_texture(vector_field const&);


   // member

   static pipeline pipeline_;

   static std::array<GLuint,2> buffer_;

   static std::array<GLuint,2> array_ptr_;

   static std::array<GLuint,2> tex_id_;

   static unsigned short frame_number_;

   static unsigned short particle_number_;

   static float aspect_ratio_;

   static float depth_;

   static std::array<float,2> rot_;

   static bool dirty_ , bbox_ , switch_;

   static std::string program_;
};

}

#endif
