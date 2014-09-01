#include <vector_field_generator.hpp>
#include <viewer.hpp>

int main(int argc,char** argv) {

   std::array<unsigned short,3> dim{{20,20,20}};

   kraken::vector_field_generator generator;
   
   kraken::viewer v(1000,800);

   v.init(argc,argv);

   v.open(generator.random(dim));

   return 0;
}
