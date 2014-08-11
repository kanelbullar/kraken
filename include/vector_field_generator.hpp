#ifndef KRAKEN_VECTOR_FIELD_GENERATOR
#define KRAKEN_VECTOR_FIELD_GENERATOR

#include <vector_field.hpp>
#include <random>
#include <iostream>
#include <progress.hpp>

namespace kraken {

typedef unsigned short ui16;
typedef std::array<ui16,3> vec3;

enum direction_type {UP, DOWN, RIGHT, LEFT, FRONT, BACK};
enum sphere_type {INSIDE, OUTSIDE};

class vector_field_generator {

   public :
   
   static vector_field const random(vec3 const&);
   static vector_field const one_direction(vec3 const&, direction_type);
   static vector_field const sphere(vec3 const&, vec3 const&, sphere_type);

};

}

#endif
