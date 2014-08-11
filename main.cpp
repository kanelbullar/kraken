#include <iostream>

#include <vector_field_generator.hpp>
#include <window.hpp>
#include <particle_emitter.hpp>

int main(int argc, char** argv) {
   
   std::cout << "Release the kraken!" << std::endl;

   /*kraken::vector_field field 
   vectorfield(kraken::vector_field_generator::
   random(std::array<unsigned short, 3>{{7,13,23}}));*/

   

   kraken::window window(1000,800);

   window.open(argc,argv);

   return 0;
}
