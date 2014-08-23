#ifndef KRAKEN_VECTOR_FIELD_GENERATOR
#define KRAKEN_VECTOR_FIELD_GENERATOR

#include <vector_field.hpp>
#include <random>
#include <iostream>
#include <progress.hpp>

namespace kraken {

typedef unsigned short ui16;
typedef float f16;
typedef std::array<ui16,3> vec3;
typedef std::array<f16,3> vec3f;

enum direction_type {UP, DOWN, RIGHT, LEFT, FRONT, BACK};
enum sphere_type {INSIDE, OUTSIDE};

class vector_field_generator {

   public :
   
   vec3f index_to_coord(unsigned long, vec3);
   vector_field const random(vec3 const&);
   vector_field const one_direction(vec3 const&, direction_type);
   vector_field const sphere(vec3 const&, vec3f const&, sphere_type);
   vector_field const tornado(vec3 const&);

};

}

#endif
