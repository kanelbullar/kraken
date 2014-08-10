#ifndef KRAKEN_PARTICLE_EMITTER
#define KRAKEN_PARTICLE_EMITTER

#include <vector>
#include <array>
#include <random>

namespace kraken {

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;
typedef std::array<float,3> pos3;

enum distribution_type {RASTER,GAUSS,RANDOM};

class particle_emitter {

   public:

   particle_emitter(distribution_type, int, vec3);
   ~particle_emitter();

   private:

   void raster(int, vec3);
   void gauss(int, vec3);
   void random(int, vec3);

   std::vector<pos3> particles_;

};

}

#endif
