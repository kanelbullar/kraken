#ifndef KRAKEN_PIPELINE
#define KRAKEN_PIPELINE

#include <gl_config.hpp>

namespace kraken {

class pipeline {

   public :

   static void init();
   static void display();
   static void key(unsigned char,int,int);
   static void time(int);

   private :

   static gl_config config_;
   static unsigned short frame_number_;
};

}

#endif
