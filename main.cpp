#include <iostream>

#include <vector_field_generator.hpp>
#include <window.hpp>

int main(int argc, char** argv) {

   std::cout << "Release the kraken!" << std::endl;

   kraken::vector_field vectorfield(kraken::vector_field_generator::random(10,10,10));

   kraken::window window(1000,800);

   window.open(argc,argv);

   return 0;
}
