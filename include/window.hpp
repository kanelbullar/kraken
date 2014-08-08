#ifndef KRAKEN_WINDOW
#define KRAKEN_WINDOW

#include <array>
#include <string>

#include <exception.hpp>
#include <pipeline.hpp>
#include <vector_field.hpp>

#include <GLFW/glfw3.h>

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
