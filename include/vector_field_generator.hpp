#ifndef KRAKEN_VECTOR_FIELD_GENERATOR
#define KRAKEN_VECTOR_FIELD_GENERATOR

#include <vector_field.hpp>

namespace kraken {

enum generation_type {RANDOM, SPHERE};

class vector_field_generator {
   public :
   
   vector_field const generate(unsigned short,
                               unsigned short,
                               unsigned short,
                               generation_type) const;
   
   private:

   vector_field const random(std::array<unsigned short, 3>) const;
   vector_field const sphere(std::array<unsigned short, 3>) const;
};

}

#endif
