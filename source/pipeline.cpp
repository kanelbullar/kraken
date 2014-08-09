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
}
