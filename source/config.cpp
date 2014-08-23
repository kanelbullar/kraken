#include <config.hpp>


namespace kraken {

void config::

init() {

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_MULTISAMPLE_ARB);

   glClearColor(0.2,0.2,0.2,1.0);

   pipeline_.add_program("glyph");
   pipeline_.set_stage("glyph","stage/vertex/pass.vert");
   pipeline_.set_stage("glyph","stage/geometry/glyph.geom");
   pipeline_.set_stage("glyph","stage/fragment/phong.frag");

   pipeline_.add_program("streamline");
   pipeline_.set_stage("streamline","stage/vertex/pass.vert");
   pipeline_.set_stage("streamline","stage/geometry/streamline.geom");
   pipeline_.set_stage("streamline","stage/fragment/simple.frag");

   pipeline_.add_program("bounding_box");
   pipeline_.set_stage("bounding_box","stage/vertex/pass.vert");
   pipeline_.set_stage("bounding_box","stage/geometry/bounding_box.geom");
   pipeline_.set_stage("bounding_box","stage/fragment/white.frag");

   pipeline_.link_programs();
}


void config::

display() {

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSwapBuffers();
   glutPostRedisplay();
}


void config::

key(unsigned char key,int x,int y) {

   unsigned short key_id(static_cast<unsigned short> (key));

   switch(key_id) {

      case  27 : glutLeaveMainLoop(); break;

      case 114 : pipeline_.link_programs(); break;
   }
}


pipeline config::pipeline_ = pipeline();

}
