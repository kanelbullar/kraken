#include <window.hpp>

namespace kraken {

   window::window(unsigned short width, unsigned short height) :
   resolution_(std::array<unsigned short,2>{width,height}),
   handle_(nullptr),
   title_("Release the kraken!"),
   frame_number_(0),
   pipeline_(pipeline())
   {}


   void window::open() {

      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
      glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
      glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

      handle_ = glfwCreateWindow(resolution_[0],
                                 resolution_[1],
                                 title_.c_str(),
                                 nullptr,
                                 nullptr);

      glfwMakeContextCurrent(handle_);
      glfwSetKeyCallback(handle_,key);

      while(!glfwWindowShouldClose(handle_)) {

         glfwPollEvents();
         pipeline_.draw();
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


   void window::

   key(GLFWwindow* window, int key, int scancode, int action, int mods) {

      switch(key) {

         case GLFW_KEY_ESCAPE :

         glfwSetWindowShouldClose(window,GL_TRUE);
         break;
      }
   }
}
