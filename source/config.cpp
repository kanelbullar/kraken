#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <config.hpp>


namespace kraken {

void config::

init(float aspect_ratio) {

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_MULTISAMPLE_ARB);

   glClearColor(0.2,0.2,0.2,1.0);

   init_programs();
   init_uniforms(aspect_ratio);

   GLuint vbo,vao;

   float center[] = {0.0,0.0,0.0};

   glGenBuffers(1,&vbo);
   glGenVertexArrays(1,&vao);

   glBindBuffer(GL_ARRAY_BUFFER,vbo);

   glBufferData(GL_ARRAY_BUFFER,sizeof(center),&center[0],GL_STATIC_DRAW);
   glBindVertexArray(vao);

   GLint attr_pos(glGetAttribLocation(1,"pos"));

   glEnableVertexAttribArray(attr_pos);
   glVertexAttribPointer(attr_pos,3,GL_FLOAT,GL_FALSE,0,0);
}


void config::

display() {

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glDrawArrays(GL_POINTS,0,10);
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


void config::

init_programs() {

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

init_uniforms(float aspect_ratio) {

   glm::mat4 projection(glm::perspective(45.0f,aspect_ratio,0.1f,100.0f)),

             view(1.0);

   view[3][2] = -25.0f;

   glm::ivec3 dim(20,20,20);

   pipeline_.uniforms_.set("projection",projection);
   pipeline_.uniforms_.set("view",view);
   pipeline_.uniforms_.set("dim",dim);

   pipeline_.set_link("glyph","projection");
   pipeline_.set_link("glyph","view");
   pipeline_.set_link("streamline","projection");
   pipeline_.set_link("streamline","view");
   pipeline_.set_link("bounding_box","projection");
   pipeline_.set_link("bounding_box","view");
   pipeline_.set_link("bounding_box","dim");

   pipeline_.enable("bounding_box");
}


pipeline config::pipeline_ = pipeline();

}
