#include <iostream>

#include <vector_field_generator.hpp>
#include <window.hpp>
#include <particle_emitter.hpp>

int main(int argc, char** argv) {
   
   std::cout << "Release the kraken!" << std::endl;

   kraken::vector_field_generator generator;

   std::array<unsigned short,3> dim {20,20,20};

   //kraken::vector_field vf (generator.sphere(dim, std::array<float,3>{{10.0,10.0,10.0}}, kraken::INSIDE));
   //kraken::vector_field vf (generator.random(dim));
   kraken::vector_field vf (generator.one_direction(dim,kraken::LEFT));

   kraken::window window(1000,800);

   window.open(argc,argv,vf);

   return 0;
}
