#include <config.hpp>

#include <viewer.hpp>

namespace kraken
{

viewer::

viewer(unsigned short width,unsigned short height) :
res_(std::array<unsigned short,2> {{width,height}})
{}


void viewer::

open() const {
   
}

void viewer::

init(int argc,char** argv) const {

   glutInit(&argc,argv);
   glutInitWindowPosition(0,0);
   glutInitWindowSize(res_[0],res_[1]);

   glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);

   glutInitContextVersion(4,4);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
   glutInitContextProfile(GLUT_CORE_PROFILE);

   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);


   glutDisplayFunc(config::display);
}

}
