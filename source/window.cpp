#include <window.hpp>
#include <iostream>

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
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
      glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
      glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

      handle_ = glfwCreateWindow(resolution_[0],
                                 resolution_[1],
                                 title_.c_str(),
                                 nullptr,
                                 nullptr);

      if(handle_ == nullptr) throw exception("window creation failed");

      glfwMakeContextCurrent(handle_);
      glfwSetKeyCallback(handle_,key);
      gl_config();

      while(!glfwWindowShouldClose(handle_)) {

         glfwPollEvents();
         pipeline_.draw();
         glDrawArrays(GL_TRIANGLES,0,9);
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
      new_title.erase(new_title.rfind('.')+3,4);
      glfwSetWindowTitle(handle_,new_title.c_str());

      if(time >= 1.0) {

         glfwSetTime(0.0);
         frame_number_ = 0;
      }

      ++frame_number_;
   }


   void window::

   gl_config() {

      glewExperimental = GL_TRUE;
      GLenum glew_init = glewInit();
      if(glew_init != GLEW_OK) throw exception("glew initialization failed");

      const char* vs = "#version 440\n"\
                       "in vec3 position;\n"\
                       "void main() {\n"\
                       "\ngl_Position = vec4(position,1.0);\n"\
                       "}";

      const char* fs = "#version 440\n"\
                       "out vec3 color;\n"\
                       "void main() {\n"\
                       "\ncolor = vec3(1.0);\n"\
                       "}";

      GLuint vs_id = glCreateShader(GL_VERTEX_SHADER),
             fs_id = glCreateShader(GL_FRAGMENT_SHADER),
             gp_id = glCreateProgram();

      glShaderSource(vs_id,1,&vs,nullptr);
      glShaderSource(fs_id,1,&fs,nullptr);
      glCompileShader(vs_id);
      glCompileShader(fs_id);

      glAttachShader(gp_id,vs_id);      
      glAttachShader(gp_id,fs_id);
      glLinkProgram(gp_id);
      glUseProgram(gp_id);

      GLfloat pos[] = {-0.5,-0.5,0.0,
                        0.5,-0.5,0.0,
                        0.0, 0.5,0.0};

      GLuint vbo,vao;
      glGenBuffers(1,&vbo);
      glGenVertexArrays(1,&vao);

      glBindBuffer(GL_ARRAY_BUFFER,vbo);
      glBufferData(GL_ARRAY_BUFFER,sizeof(pos),pos,GL_STATIC_DRAW);
      glBindVertexArray(vao);

      GLint attr_pos = glGetAttribLocation(gp_id,"position");
      glEnableVertexAttribArray(attr_pos);
      glVertexAttribPointer(attr_pos,3,GL_FLOAT,GL_FALSE,0,0);
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
