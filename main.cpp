#include <vector_field_generator.hpp>
#include <vector_field_loader.hpp>
#include <viewer.hpp>

int main(int argc,char** argv) {

   kraken::transfer_function trans;

   trans.add(0.0,kraken::rgba{{1.0,0.0,0.0,1.0}});
   trans.add(0.1,kraken::rgba{{1.0,0.0,0.0,0.3}});
   trans.add(0.5,kraken::rgba{{0.0,0.0,1.0,0.0}});

   std::array<unsigned short,3> dim{{128,128,128}};

   kraken::vector_field_loader loader;
   
   kraken::viewer v(1000,800);

   v.init(argc,argv);

   if(argc == 2 && std::string("random").compare(argv[1]) == 0) {

      kraken::vector_field_generator generator;
      v.open(generator.random(dim),trans);
   }

   else if(argc == 2 && std::string("cylinder").compare(argv[1]) == 0) {

      v.open(loader.load("data/cylinder.raw",dim),trans);
   }

   else v.open(loader.load("data/tornado.raw",dim),trans);


   return 0;
}
