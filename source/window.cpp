#include <window.hpp>

namespace kraken {

   window::window(unsigned short width,unsigned short height) :
   res_(std::array<unsigned short,2>{width,height}),
   title_("Release the kraken!"),
   handle_(-1)
   {}


   void window::

   open(int argc, char ** argv) {

      glutInit(&argc,argv);
      glutInitWindowPosition(0,0);
      glutInitWindowSize(res_[0],res_[1]);

      glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
      glutInitContextVersion(3,3);
      glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
      glutInitContextProfile(GLUT_CORE_PROFILE);

      glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                    GLUT_ACTION_GLUTMAINLOOP_RETURNS);

      handle_ = glutCreateWindow(title_.c_str());

      glewExperimental = GL_TRUE;
      GLenum glew_init = glewInit();

      if(glew_init != GLEW_OK) throw exception("glew initialisation failed");

      pipeline::init();
      glutDisplayFunc(pipeline::display);
      glutTimerFunc(250,pipeline::time,0);
      glutKeyboardFunc(pipeline::key);

      glutMainLoop();
   }
}
