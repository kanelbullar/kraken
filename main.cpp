#include <iostream>

#include <vector_field_generator.hpp>
#include <window.hpp>

int main(int argc, char* argv[]) {

   std::cout << "Release the kraken!" << std::endl;
   kraken::window window(1000,800);
   window.open();

   return 0;
}
