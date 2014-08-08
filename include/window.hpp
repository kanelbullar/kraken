#ifndef KRAKEN_WINDOW
#define KRAKEN_WINDOW

#include <GLFW/glfw3.h>
#include <array>
#include <string>

namespace kraken {

class window {

   public:

   window(unsigned short, unsigned short);
   
   void open();

   private:

   void fps_display();

   std::array<unsigned short,2> resolution_;
   GLFWwindow*                  handle_;
   std::string                  title_;
   unsigned short               frame_number_;
};

}

#endif
