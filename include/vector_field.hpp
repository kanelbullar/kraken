#ifndef KRAKEN_VECTOR_FIELD
#define KRAKEN_VECTOR_FIELD

#include <array>

namespace kraken {

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;

struct vector_field {

   vector_field(std::array<unsigned short,3> const&, void*, float, float);
   ~vector_field();

   std::array<unsigned short,3> dim_;
   void* data_;
   float min_, max_;
};

}

#endif
