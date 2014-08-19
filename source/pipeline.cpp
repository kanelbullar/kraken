#include <pipeline.hpp>

#include <iostream>

namespace kraken {

   void pipeline::

   init(vector_field const& vf,std::array<unsigned short,2> const& res) {

      glClearColor(0.2,0.2,0.2,1.0);
      glEnable(GL_MULTISAMPLE_ARB);
      glEnable(GL_DEPTH_TEST);

      std::array<std::string,3> 

      glyph_stages      = {{"pass","glyph","phong"}},
      streamline_stages = {{"pass","streamline","simple"}};

      config_.add_shader(glyph_stages[0],GL_VERTEX_SHADER);
      config_.add_shader(glyph_stages[1],GL_GEOMETRY_SHADER);
      config_.add_shader(streamline_stages[1],GL_GEOMETRY_SHADER);
      config_.add_shader(glyph_stages[2],GL_FRAGMENT_SHADER);
      config_.add_shader(streamline_stages[2],GL_FRAGMENT_SHADER);

      config_.add_program("glyph",glyph_stages);
      config_.add_program("streamline",streamline_stages);
      config_.enable_program("streamline");

      config_.aspect_ratio(res);
      config_.load_default(vf);
   }

   void pipeline::display() {

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDrawArrays(GL_POINTS,0,config_.particle_number());
      glutSwapBuffers();
      glutPostRedisplay();
      update();

      ++frame_number_;
   }


   void pipeline::key(unsigned char key, int x, int y) {

      unsigned short key_id = static_cast<unsigned short> (key);

      switch(key_id) {

         case 27  : glutLeaveMainLoop(); break;

         case 43  : config_.zoom(true) ;  view_changed_ = true ; break;

         case 45  : config_.zoom(false) ; view_changed_ = true ; break;

         case 49  :  break;

         case 50  :  break;

         case 114 : config_.reload_shader(); break;
      }
   }


   void pipeline::special(int key, int x, int y) {

      switch(key) {
         
         case 100 : config_.rotate(false,false) ; view_changed_ = true ; break;

         case 102 : config_.rotate(false,true)  ; view_changed_ = true ; break;

         case 103 : config_.rotate(true,false)  ; view_changed_ = true ; break;

         case 101 : config_.rotate(true,true)   ; view_changed_ = true ; break;
      }
   }


   void pipeline::reshape(int width , int height) {

      std::array<unsigned short,2> res;

      res[0] = static_cast<unsigned short> (width);
      res[1] = static_cast<unsigned short> (height);

      config_.aspect_ratio(res);

      proj_changed_ = true;
   }


   void pipeline::time(int init) {

      unsigned short fps(4*frame_number_);

      std::string new_title("Release the kraken!   |   FPS : ");
      new_title.append(std::to_string(fps));

      glutSetWindowTitle(new_title.c_str());
      frame_number_ = 0;

      glutTimerFunc(250,time,0);
   }


   void pipeline::update() {

      if(view_changed_) {

         config_.load_model();
         view_changed_ = false;
      }

      if(proj_changed_) {

         config_.load_projection();
         proj_changed_ = false;
      } 
   }


   // initialize static member

   gl_config pipeline::config_ = gl_config();

   unsigned short pipeline::frame_number_ = 0;

   bool pipeline::view_changed_ = false;
   bool pipeline::proj_changed_ = false;
}
