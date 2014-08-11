#ifndef KRAKEN_VECTOR_FIELD
#define KRAKEN_VECTOR_FIELD

#include <array>

namespace kraken {

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;

struct vector_field {

   vector_field(std::array<unsigned short,3> const&, void*);
   ~vector_field();
   std::array<unsigned short,3> index_to_coord(unsigned long);

   std::array<unsigned short,3> dim_;
   void* data_;
};

}

#endif
