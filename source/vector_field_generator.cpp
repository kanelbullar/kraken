#include <vector_field_generator.hpp>
#include <cmath>

namespace kraken {

   vec3f vector_field_generator::index_to_coord(unsigned long index, vec3 dim) {      
      float z = index / (dim[0] * dim[1]);
      float y = (index - (z * dim[0] * dim[1]))/dim[0];
      //y = reinterpret_cast<float> (reinterpret_cast<int> (y));
      float x = index - (z * dim[0] * dim[1]);
      return vec3f{{x,y,z}};
   }

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


   // ONE DIRECTION
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


   // SPEHRE TODO: TYPE anpassen
   vector_field const vector_field_generator::

   sphere(vec3 const& dim, vec3f const& center, sphere_type type) {
      
      unsigned long size = dim[0]*dim[1]*dim[2]*3;

      float* data = new float[size];

      unsigned long index = 0;

      for(unsigned short z = 0 ; z < dim[2] ; ++z) {  
         for(unsigned short y = 0 ; y < dim[1] ; ++y) {  
            for(unsigned short x = 0 ; x < dim[0] ; ++x) {  
               data[index]   = center[0] - x;
               data[++index] = center[1] - y;
               data[++index] = center[2] - z;
               ++index;
            }
         }
      }

      void* data_ptr = reinterpret_cast<void*> (data);

      return vector_field(dim, data_ptr, 0, 1);
   }


   // TORNADO
   vector_field const vector_field_generator::tornado(vec3 const& dim) {
      
      unsigned long size = dim[0]*dim[1]*dim[2]*3;

      float* data = new float[size];

      unsigned long index = 0;

      vec3f dl {{-1.0,0.0,-1.0}};
      vec3f dr {{-1.0,0.0, 1.0}};
      vec3f ul {{ 1.0,0.0,-1.0}};
      vec3f ur {{ 1.0,0.0, 1.0}};

      int leveldim = 0;
      float step;
      
      for(float z = 0 ; z > -dim[2] ; --z) {  
         for(float y = 0 ; y < dim[1] ; ++y) {  
            for(float x = 0 ; x < dim[0] ; ++x) {  
               
               if (dim[0]%2 != 0 && x == (dim[0]-1)/2 && abs(z) == (dim[0]-1)/2) {
                  data[index]   = 0.0;
                  data[++index] = 0.0;
                  data[++index] = 0.0;
                  ++index;
               }

               // DOWN LEFT DIAGONAL               
               else if(abs(z) == x && abs(z) < (dim[2] / 2) && x < (dim[0] / 2) ) {
                  data[index]   = dl[0];
                  data[++index] = dl[1];
                  data[++index] = dl[2];
                  ++index;
               }

               // UP RIGHT DIAGONAL
               else if(abs(z) == x && x > (dim[0] / 2) && abs(z) > (dim[2] / 2 ) ) {
                  data[index]   = ur[0];
                  data[++index] = ur[1];
                  data[++index] = ur[2];
                  ++index;
               }

               // UP LEFT DIAGONAL
               else if(abs(z) == dim[0] - x) {
                  data[index]   = ul[0];
                  data[++index] = ul[1];
                  data[++index] = ul[2];
                  ++index;
               }

               // DOWN RIGHT DIAGONAL
               else if(x == dim[2] - abs(z)) {
                  data[index]   = dr[0];
                  data[++index] = dr[1];
                  data[++index] = dr[2];
                  ++index;
               }
                  
               // LEFT TRIANGLE
               else if(abs(z) > x && x < (dim[0] / 2) ) {
                  leveldim = dim[2] - ( 2 * x );
                  std::cout<<"index: "<<index/3<<" leveldim: "<<leveldim<<" LT"<<std::endl;
                  step = 1/(leveldim-1);
                  data[index]   = dl[0] * ( 1 - ( abs(z) * step ) + ul[0] * ( abs(z) * step) );
                  data[++index] = dl[1] * ( 1 - ( abs(z) * step ) + ul[1] * ( abs(z) * step) );
                  data[++index] = dl[2] * ( 1 - ( abs(z) * step ) + ul[2] * ( abs(z) * step) );
                  ++index;
               }

               // DOWN TRIANGLE
               else if(x > abs(z) && abs(z) < (dim[2] / 2) ) {
                  leveldim = dim[0] - ( 2 * abs(z) );
                  std::cout<<"index: "<<index/3<<" leveldim: "<<leveldim<<" DT"<<std::endl;
                  step = 1/(leveldim-1);
                  data[index]   = dl[0] * ( 1 - ( x * step ) + dr[0] * ( x * step) );
                  data[++index] = dl[1] * ( 1 - ( x * step ) + dr[1] * ( x * step) );
                  data[++index] = dl[2] * ( 1 - ( x * step ) + dr[2] * ( x * step) );
                  ++index;
               }

               // RIGHT TRIANGLE
               else if(x > abs(z) && x > (dim[0] / 2) ) {
                  leveldim = dim[2] - ( dim[0] - x ) * 2;
                  std::cout<<"index: "<<index/3<<" leveldim: "<<leveldim<<" RT"<<std::endl;
                  step = 1/(leveldim-1);
                  data[index]   = dr[0] * ( 1 - ( abs(z) * step ) + ur[0] * ( abs(z) * step) );
                  data[++index] = dr[1] * ( 1 - ( abs(z) * step ) + ur[1] * ( abs(z) * step) );
                  data[++index] = dr[2] * ( 1 - ( abs(z) * step ) + ur[2] * ( abs(z) * step) );
                  ++index;
               }

               // UP TRIANGLE
               else if(abs(z) > x && abs(z) > (dim[2] / 2) ) {
                  leveldim = dim[0] - ( dim[2] - abs(z) ) * 2;
                  std::cout<<"index: "<<index/3<<" leveldim: "<<leveldim<<" UT"<<std::endl;
                  step = 1/(leveldim-1);
                  data[index]   = ul[0] * ( 1 - ( x * step ) + ur[0] * ( x * step) );
                  data[++index] = ul[1] * ( 1 - ( x * step ) + ur[1] * ( x * step) );
                  data[++index] = ul[2] * ( 1 - ( x * step ) + ur[2] * ( x * step) );
                  ++index;
               }
            }
         }
      }

      void* data_ptr = reinterpret_cast<void*> (data);
            
      
      return vector_field(dim, data_ptr, 0, 1);
   }

}
