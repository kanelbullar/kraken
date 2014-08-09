#include <vector_field_generator.hpp>

namespace kraken {

   /*vector_field const vector_field_generator::
   
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
   }*/

   vector_field const vector_field_generator::

   random(unsigned short width, 
          unsigned short height, 
          unsigned short depth) {

      std::default_random_engine generator;
      std::uniform_real_distribution<float> distribution(0,1);
   
      std::array<unsigned short, 3> dim {width,height,depth};   

      unsigned long size = width*height*depth;

      float* data = new float[size];

      for(unsigned long index = 0 ; index < size ; ++index)
      {
         data[index] = distribution(generator);
      }

      void* data_ptr = reinterpret_cast<void*> (data);
   
      return vector_field(dim, data_ptr);
   }


   vector_field const vector_field_generator::

   sphere(unsigned short width, 
          unsigned short height, 
          unsigned short depth) {

      std::array<unsigned short, 3> dim {width,height,depth};
      
      return vector_field(dim, nullptr);
   }

}
