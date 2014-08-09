#include <pipeline.hpp>

#include <iostream>

namespace kraken {

   void pipeline::

   display() {

      glClearColor(0.2,0.2,0.2,1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      glutSwapBuffers();
      glutPostRedisplay();
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
}
