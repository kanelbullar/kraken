#ifndef KRAKEN_WINDOW
#define KRAKEN_WINDOW

#include <array>
#include <string>

#include <GLFW/glfw3.h>

#include <exception.hpp>
#include <pipeline.hpp>

namespace kraken {

class window {

   public:

   window(unsigned short, unsigned short);
   
   void open();

   private:

   void fps_display();

   // callback functions
   static void key(GLFWwindow*, int, int, int, int);

   std::array<unsigned short,2> resolution_;
   GLFWwindow*                  handle_;
   std::string                  title_;
   unsigned short               frame_number_;
   pipeline                     pipeline_;
};

}

#endif
