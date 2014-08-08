#ifndef KRAKEN_VECTOR_FIELD
#define KRAKEN_VECTOR_FIELD

#include <array>

#include <GL/gl.h>

namespace kraken {

struct vector_field {

   vector_field(std::array<unsigned short,3> const&, GLvoid*);
   ~vector_field();

   std::array<unsigned short,3> dim_;
   GLvoid* data_;
};

}

#endif
