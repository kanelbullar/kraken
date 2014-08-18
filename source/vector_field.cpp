#include <vector_field.hpp>

namespace kraken {

   vector_field::
   
   vector_field(std::array<unsigned short,3> const& dim, void* data, 
                float min, float max) :
   dim_(dim),
   data_(data),
   min_(min),
   max_(max)   
   {}


   vector_field::

   ~vector_field() {

      float* data = reinterpret_cast<float*> (data_);

      delete[] data;
   }

   vec3 vector_field::index_to_coord(unsigned long index) {
      unsigned short z = index / dim_[0] * dim_[1];
      unsigned short y = index - (z*dim_[0]*dim_[1]);
      unsigned short x = index - (y*dim_[0]);
      return vec3{{x,y,z}};
   }
}
