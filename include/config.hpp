#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <pipeline.hpp>

#include <GL/freeglut.h>

namespace kraken {

class config {

   public :

   static void init(float);

   static void display();

   static void key(unsigned char,int,int);


   private :

   static void init_programs();

   static void init_uniforms(float);


   static pipeline pipeline_;
};

}

#endif
