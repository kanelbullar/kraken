#include <pipeline.hpp>

#include <iostream>

namespace kraken {

unsigned short pipeline::frame_number_ = 0;

   void pipeline::

   display() {

      glClearColor(0.2,0.2,0.2,1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      glutSwapBuffers();
      glutPostRedisplay();

      ++frame_number_;
   }


   void pipeline::

   key(unsigned char key, int x, int y) {

      unsigned short key_id = static_cast<unsigned short> (key);

      switch(key_id)
      {
         case 27 :

         glutLeaveMainLoop();
         break;
      }
   }


   void pipeline::

   time(int init) {

      unsigned short fps(4*frame_number_);

      std::string new_title("Release the kraken!   |   FPS : ");
      new_title.append(std::to_string(fps));

      glutSetWindowTitle(new_title.c_str());
      frame_number_ = 0;

      glutTimerFunc(250,time,0);
   }
}
