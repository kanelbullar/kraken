#include <particle_emitter.hpp>

namespace kraken {
   particle_emitter::particle_emitter(distribution_type type, int number) {
      switch (type) {
         case RASTER: raster(number); break;
         
         case GAUSS:  gauss(number);  break;

         case RANDOM: random(number); break;
      }
   }

   void particle_emitter::raster(int number) {
      
   }

   void particle_emitter::gauss(int number) {

   }

   void particle_emitter::random(int number){
      
   }
}
