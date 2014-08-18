#include <pipeline.hpp>

#include <iostream>

namespace kraken {

   void pipeline::init(vector_field const& vf) {

      glClearColor(0.2,0.2,0.2,1.0);
      glEnable(GL_MULTISAMPLE_ARB);
      glEnable(GL_DEPTH_TEST);

      //glViewport(0,0,1000,800);

      std::array<std::string,3> shader_stages = {{"pass",
                                                  "streamline",
                                                  "simple"}};

      config_.add_shader(shader_stages[0],GL_VERTEX_SHADER);
      config_.add_shader(shader_stages[1],GL_GEOMETRY_SHADER);
      config_.add_shader(shader_stages[2],GL_FRAGMENT_SHADER);
      config_.add_program("triangle",shader_stages);
      config_.enable_program("triangle");

      config_.load_default(vf);
   }

   void pipeline::display() {

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDrawArrays(GL_POINTS,0,160000);
      glutSwapBuffers();
      glutPostRedisplay();
      
      if(model_changed_) {

         config_.load_model();
         model_changed_ = false;
      }

      ++frame_number_;
   }


   void pipeline::key(unsigned char key, int x, int y) {

      unsigned short key_id = static_cast<unsigned short> (key);

      switch(key_id) {

         case 27  : glutLeaveMainLoop(); break;

         case 114 : config_.reload_shader(); break;

      }
   }


   void pipeline::special(int key, int x, int y) {

      switch(key) {
         
         case 100 : config_.rotate(false,false) ; model_changed_ = true ; break;

         case 102 : config_.rotate(false,true)  ; model_changed_ = true ; break;

         case 103 : config_.rotate(true,false)  ; model_changed_ = true ; break;

         case 101 : config_.rotate(true,true)   ; model_changed_ = true ; break;
      }
   }


   void pipeline::time(int init) {

      unsigned short fps(4*frame_number_);

      std::string new_title("Release the kraken!   |   FPS : ");
      new_title.append(std::to_string(fps));

      glutSetWindowTitle(new_title.c_str());
      frame_number_ = 0;

      glutTimerFunc(250,time,0);
   }


   gl_config pipeline::config_ = gl_config();
   unsigned short pipeline::frame_number_ = 0;
   bool pipeline::model_changed_ = false;
}
