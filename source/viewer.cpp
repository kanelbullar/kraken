#include <viewer.hpp>

#include <iostream>

namespace kraken
{

viewer::

viewer(unsigned short width,unsigned short height) :
handle_(-1),
res_(std::array<unsigned short,2> {{width,height}})
{}


void viewer::

open(vector_field const& vf) {

   handle_ = glutCreateWindow("Kraken");

   if(handle_ < 0) {

      std::cerr << std::endl
                << "couldn't create window"
                << std::endl;
   }

   else {

      glewExperimental = GL_TRUE;
      GLenum init(glewInit());

      if(init != GLEW_OK) {

         std::cerr << std::endl
                  << glewGetErrorString(init)
                  << std::endl;

         glutExit();
      }

      else {

         float aspect_ratio(static_cast<float> (res_[0]));

         aspect_ratio /= res_[1];

         // register callback functions
         glutDisplayFunc(config::display);
         glutKeyboardFunc(config::key);
         glutTimerFunc(0,config::time,0);

         // init config
         config::init(aspect_ratio);
         config::bind_field(vf);

         glutMainLoop();

         // clear buffer
         config::clear();
         glutExit();
      }
   }
}

void viewer::

init(int argc,char** argv) const {

   glutInit(&argc,argv);
   glutInitWindowPosition(0,0);
   glutInitWindowSize(res_[0],res_[1]);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

   glutInitContextVersion(4,4);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
   glutInitContextProfile(GLUT_CORE_PROFILE);

   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

}
