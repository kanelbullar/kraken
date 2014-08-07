#ifndef KRAKEN_WINDOW
#define KRAKEN_WINDOW

#include <GLFW/glfw3.h>
#include <array>

namespace kraken {

class window {

   public:

   window(unsigned short, unsigned short);
   
   void open();

   private:

   std::array<unsigned short,2> resolution_;
   GLFWwindow* handle_;

};

}

#endif
