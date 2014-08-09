#include <vector_field_generator.hpp>

namespace kraken {

   // RANDOM
   vector_field const vector_field_generator::

   random(vec3 const& dim) {

      std::default_random_engine generator;
      std::uniform_real_distribution<float> distribution(0,1);  

      unsigned long size = dim[0]*dim[1]*dim[2];

      float* data = new float[size];

      for(unsigned long index = 0 ; index < size ; ++index) {
         data[index] = distribution(generator);
      }

      void* data_ptr = reinterpret_cast<void*> (data);
   
      return vector_field(dim, data_ptr);
   }

   //ONE DIRECTION
   vector_field const vector_field_generator::

   one_direction(vec3 dim,
                 direction_type type) {  

      unsigned long size = dim[0]*dim[1]*dim[2];

      float* data = new float[size];

      int x(0), y(0), z(0);

      switch (type) {
         
         case UP:    y =  1;   break;

         case DOWN:  y = -1;   break;

         case RIGHT: x =  1;   break;

         case LEFT:  x = -1;   break;

         case FRONT: z =  1;   break;

         case BACK:  z = -1;   break;
      }
      
      for(unsigned long index = 0 ; index < size ; ++index) {  
            data[index]   = x;
            data[++index] = y;
            data[++index] = z;
      }

      void* data_ptr = reinterpret_cast<void*> (data);
   
      return vector_field(dim, data_ptr);
   }

   //SPHERE
   vector_field const vector_field_generator::

   sphere(vec3 dim, sphere_type type, vec3 center) {
      
      return vector_field(dim, nullptr);
   }

}
