#ifndef KRAKEN_VECTOR_FIELD
#define KRAKEN_VECTOR_FIELD

#include <GL/gl.h>
#include <array>

namespace kraken {

struct vector_field {
   vector_field(std::array<unsigned short,3> const&, GLvoid*);

   std::array<unsigned short,3> dim_;
   GLvoid* data_;
};

}

#endif
