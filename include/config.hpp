#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <pipeline.hpp>

#include <GL/freeglut.h>

namespace kraken {

class config {

   public :

   static void init();

   static void display();

   static void key(unsigned char,int,int);

   private :

   static pipeline pipeline_;
};

}

#endif
