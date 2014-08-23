#include <viewer.hpp>

int main(int argc,char** argv) {
   
   kraken::viewer v(1000,800);

   v.init(argc,argv);
   v.open();

   return 0;
}
