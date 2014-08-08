#ifndef KRAKEN_VECTOR_FIELD
#define KRAKEN_VECTOR_FIELD

#include <array>

namespace kraken {

struct vector_field {

   vector_field(std::array<unsigned short,3> const&, void*);
   ~vector_field();

   std::array<unsigned short,3> dim_;
   void* data_;
};

}

#endif
