#ifndef KRAKEN_PIPELINE
#define KRAKEN_PIPELINE

#include <gl_config.hpp>
#include <vector_field.hpp>

namespace kraken {

class pipeline {

   public :

   static void init(vector_field const&,std::array<unsigned short,2> const&);

   static void display();
   static void key(unsigned char,int,int);
   static void reshape(int,int);
   static void special(int,int,int);
   static void time(int);

   private :

   static void update();

   static gl_config config_;
   static unsigned short frame_number_;
   static bool model_changed_;
   static bool ratio_changed_;
};

}

#endif
