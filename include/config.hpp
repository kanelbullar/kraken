#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <pipeline.hpp>
#include <vector_field.hpp>

#include <GL/freeglut.h>

namespace kraken {

class config {

   public :

   // callback functions

   static void display();

   static void key(unsigned char,int,int);

   static void time(int);


   // support functions

   static void init(float);

   static void bind_field(vector_field const&);

   static void clear();


   private :

   static void init_programs();

   static void init_uniforms(float);

   static void init_memory(std::array<unsigned short,3> const&);

   static void init_texture(vector_field const&);


   // member

   static pipeline pipeline_;

   static std::array<GLuint,2> buffer_;

   static std::array<GLuint,2> array_ptr_;

   static GLuint tex_id_;

   static unsigned short frame_number_;

   static unsigned short particle_number_;

   static bool dirty_ , bbox_ , switch_;

   static std::string program_;
};

}

#endif
