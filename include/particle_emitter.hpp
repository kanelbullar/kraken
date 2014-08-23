#ifndef KRAKEN_PARTICLE_EMITTER
#define KRAKEN_PARTICLE_EMITTER

#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <vector_field_generator.hpp>

namespace kraken {

struct particles {

   inline particles(unsigned size, void* data):size_(size),data_(data){}
   inline ~particles() {
      float* data_ptr = reinterpret_cast<float*> (data_);
      delete [] data_ptr;
   }
   
   unsigned size_;
   void* data_;
   
};

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;
typedef std::array<float,3> pos3;

class particle_emitter {

   public:

   particle_emitter();
   ~particle_emitter();

   particles const raster(int, vec3 const&) const;
   particles const gauss(int, vec3 const&)  const;
   particles const random(int, vec3 const&) const;
   particles const cube(int, vec3 const&, vec3 const&, kraken::direction_type);

   private:

   particles const convert(std::vector<pos3> const&) const;

};

}

#endif
