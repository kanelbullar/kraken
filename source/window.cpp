#include <window.hpp>

namespace kraken {

   window::window(unsigned short width,unsigned short height) :
   res_(std::array<unsigned short,2>{width,height}),
   title_("Kraken")
   {}


   void window::

   open(int argc, char ** argv) {

      glutInit(&argc,argv);
      glutInitWindowPosition(0,0);
      glutInitWindowSize(res_[0],res_[1]);
      glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
      glutCreateWindow(title_.c_str());

      glutDisplayFunc(pipeline::display);

      glutMainLoop();
   }
}
