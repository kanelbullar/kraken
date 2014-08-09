#ifndef KRAKEN_PIPELINE
#define KRAKEN_PIPELINE

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace kraken {

class pipeline {

   public :

   static void display();
   static void key(unsigned char,int,int);
   static void time(int);

   static unsigned short frame_number_;
};

}

#endif
