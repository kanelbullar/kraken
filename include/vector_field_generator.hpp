#ifndef KRAKEN_VECTOR_FIELD_GENERATOR
#define KRAKEN_VECTOR_FIELD_GENERATOR

#include <vector_field.hpp>
#include <random>
#include <iostream>

namespace kraken {

enum generation_type {RANDOM, SPHERE};

class vector_field_generator {

   public :
   
   static vector_field const random(unsigned short, unsigned short, unsigned short);
   static vector_field const sphere(unsigned short, unsigned short, unsigned short);

};

}

#endif
