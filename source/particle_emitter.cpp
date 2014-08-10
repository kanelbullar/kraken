#include <particle_emitter.hpp>

namespace kraken {
   particle_emitter::particle_emitter(distribution_type type, 
                                      int number, 
                                      vec3 dim) {
      switch (type) {
         case RASTER: raster(number, dim); break;
         
         case GAUSS:  gauss(number, dim);  break;

         case RANDOM: random(number, dim); break;
      }
   }

   particle_emitter::~particle_emitter() {

   }

   void particle_emitter::raster(int number, vec3 dim) {
      float number_f = static_cast<float>(number);      
      
      for(float z = -(dim[2]/2); z < dim[2]/2; z+=dim[2]/number_f) {
         for(float y = -(dim[1]/2); y < dim[1]/2; y+=dim[1]/number_f) {
            for(float x = -(dim[0]/2); x < dim[0]/2; x+=dim[0]/number_f) {
               particles_.push_back(pos3{x,y,z});
            }
         }
      }
   }

   void particle_emitter::gauss(int number, vec3 dim) {
      
   }

   // TODO: Abfangen, dass Punkte nicht doppelt vergeben werden
   void particle_emitter::random(int number, vec3 dim) {

      std::default_random_engine generator;
      std::uniform_real_distribution<float> x_dist(-(dim[0]/2),dim[0]/2);
      std::uniform_real_distribution<float> y_dist(-(dim[1]/2),dim[1]/2);
      std::uniform_real_distribution<float> z_dist(-(dim[2]/2),dim[2]/2);  

      for(int index = 0; index < number; ++index) {
         particles_.push_back(pos3{x_dist(generator),
                                   y_dist(generator),
                                   z_dist(generator)});
      }
   }
}
