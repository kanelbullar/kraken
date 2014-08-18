#include <vector_field_generator.hpp>
#include <cmath>

namespace kraken {

   // RANDOM
   vector_field const vector_field_generator::

   random(vec3 const& dim) {

      std::default_random_engine generator;
      std::uniform_real_distribution<float> distribution(-1,1);  

      float min = 0.0, max = 0.0, absolute = 0.0;
      unsigned long size = dim[0]*dim[1]*dim[2]*3;

      float* data = new float[size];

      progress status("RANDOM VECTOR FIELD",size);
      for(unsigned long index = 0 ; index < size ; ++index) {
         data[index]   = distribution(generator);
         data[++index] = distribution(generator);
         data[++index] = distribution(generator);
         absolute = sqrt(pow(data[index]  ,2) + 
                         pow(data[index-1],2) + 
                         pow(data[index-2],2));

         if     (absolute < min) min = absolute;
         else if(absolute > max) max = absolute;

         status.update(index);
      }
      status.finalize();

      void* data_ptr = reinterpret_cast<void*> (data);
   
      return vector_field(dim, data_ptr, min, max);
   }

   //ONE DIRECTION
   vector_field const vector_field_generator::

   one_direction(vec3 const& dim, direction_type type) {  

      unsigned long size = dim[0]*dim[1]*dim[2]*3;

      float* data = new float[size];

      float x(0), y(0), z(0);

      switch (type) {
         
         case UP    :  y =  1;   break;

         case DOWN  :  y = -1;   break;

         case RIGHT :  x =  1;   break;

         case LEFT  :  x = -1;   break;

         case FRONT :  z =  1;   break;

         case BACK  :  z = -1;   break;
      }
      
      for(unsigned long index = 0 ; index < size ; ++index) {  
            data[index]   = x;
            data[++index] = y;
            data[++index] = z;
      }

      void* data_ptr = reinterpret_cast<void*> (data);
   
      return vector_field(dim, data_ptr, 0, 1);
   }

   // TODO: SPHERE
   vector_field const vector_field_generator::

   sphere(vec3 const& dim, vec3 const& center, sphere_type type) {
      
      return vector_field(dim, nullptr, 0, 0);
   }

}
