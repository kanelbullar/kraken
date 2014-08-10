#ifndef KRAKEN_PARTICLE_EMITTER
#define KRAKEN_PARTICLE_EMITTER

#include <vector>

namespace kraken {

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;

enum distribution_type {RASTER,GAUSS,RANDOM};

class particle_emitter {

   public:

   particle_emitter(distribution_type, int);
   ~particle_emitter();

   private:

   void raster(int);
   void gauss(int);
   void random(int);

   std::vector<vec3> particles_;

};

}

#endif
