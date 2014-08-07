#include <vector_field_generator.hpp>

namespace kraken {

   vector_field const vector_field_generator::
   
   generate(unsigned short width, 
            unsigned short height,
            unsigned short depth, 
            generation_type type) const {

      std::array<unsigned short, 3> dim {width,height,depth};

      switch(type) {
         case RANDOM: return random(dim);
         case SPHERE: return sphere(dim);
         default:     return vector_field(dim,nullptr);   
      }
   }


   vector_field const vector_field_generator::

   random(std::array<unsigned short, 3> dim) const {

      unsigned long size = dim[0]*dim[1]*dim[2];

      GLfloat* data = new float[size];

      for(unsigned long index = 0 ; index < size ; ++index)
      {
         data[index] = 0;
      }

      GLvoid* data_ptr = reinterpret_cast<GLvoid*> (data);
   
      return vector_field(dim,data_ptr);
   }


   vector_field const vector_field_generator::

   sphere(std::array<unsigned short, 3> dim) const {
      
      return vector_field(dim,nullptr);
   }

}
