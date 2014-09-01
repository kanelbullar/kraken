#include <vector_field_generator.hpp>
#include <vector_field_loader.hpp>
#include <viewer.hpp>

int main(int argc,char** argv) {

   std::array<unsigned short,3> dim{{128,128,128}};

   kraken::vector_field_loader loader;

   //kraken::vector_field_generator generator;
   
   kraken::viewer v(1000,800);

   v.init(argc,argv);

   //v.open(generator.random(dim));

   v.open(loader.load("data/tornado.raw",dim));

   return 0;
}
