#include <vector_field.hpp>

namespace kraken {

   vector_field::
   
   vector_field(std::array<unsigned short,3> const& dim, void* data) :
   dim_(dim),
   data_(data)   
   {}


   vector_field::

   ~vector_field() {

      float* data = reinterpret_cast<float*> (data_);

      delete[] data;
   }
}
