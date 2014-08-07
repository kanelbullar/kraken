#include <window.hpp>

namespace kraken {

   window::window(unsigned short width, unsigned short height) :
   resolution_(std::array<unsigned short,2>{width,height}),
   handle_(nullptr)
   {}

   void window::open() {
      glfwInit();
      handle_ = glfwCreateWindow(resolution_[0],
                                 resolution_[1],
                                 "Release the kraken!",
                                 nullptr,
                                 nullptr);
      while(!glfwWindowShouldClose(handle_)) {
         glfwPollEvents();
      }
      
   }

}
