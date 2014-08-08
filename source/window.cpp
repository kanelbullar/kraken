#include <window.hpp>

namespace kraken {

   window::window(unsigned short width, unsigned short height) :
   resolution_(std::array<unsigned short,2>{width,height}),
   handle_(nullptr),
   title_("Release the kraken!"),
   frame_number_(0)
   {}


   void window::open() {

      glfwInit();

      handle_ = glfwCreateWindow(resolution_[0],
                                 resolution_[1],
                                 title_.c_str(),
                                 nullptr,
                                 nullptr);

      while(!glfwWindowShouldClose(handle_)) {

         glfwPollEvents();
         glfwSwapBuffers(handle_);
         fps_display();
      }
      
      glfwTerminate();
   }


   void window::

   fps_display() {

      double      time(glfwGetTime());
      std::string new_title(title_);

      new_title.append("  |  FPS : ");      
      new_title.append(std::to_string(frame_number_/time));
      glfwSetWindowTitle(handle_,new_title.c_str());

      if(time >= 1.0) {

         glfwSetTime(0.0);
         frame_number_ = 0;
      }

      ++frame_number_;
   }

}
