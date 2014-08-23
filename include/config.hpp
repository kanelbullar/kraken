#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <pipeline.hpp>
#include <vector_field.hpp>

#include <GL/freeglut.h>

namespace kraken {

class config {

   public :

   static void init(float);

   static void display();

   static void key(unsigned char,int,int);

   static void time(int);

   static void bind_field(vector_field const&);


   private :

   static void init_programs();

   static void init_uniforms(float);


   static pipeline pipeline_;

   static unsigned short frame_number_;

   static unsigned short particle_number_;
};

}

#endif
