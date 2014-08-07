#include <vector_field.hpp>

namespace kraken {
   vector_field(std::array<unsigned short,3> const& dim, GLvoid* data) :
   dim_(dim),
   data_(data)   
   {}
}
