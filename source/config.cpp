#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <config.hpp>
#include <particle_emitter.hpp>


namespace kraken {

void config::

init(float aspect_ratio) {

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_MULTISAMPLE_ARB);

   glClearColor(0.2,0.2,0.2,1.0);

   init_programs();
   init_uniforms(aspect_ratio);
}


void config::

display() {

   pipeline_.enable("glyph");
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glDrawArrays(GL_POINTS,0,particle_number_);
   glutSwapBuffers();
   glutPostRedisplay();
   
   ++frame_number_;
}


void config::

key(unsigned char key,int x,int y) {

   unsigned short key_id(static_cast<unsigned short> (key));

   switch(key_id) {

      case  27 : glutLeaveMainLoop(); break;

      case 114 : pipeline_.link_programs(); break;
   }
}

void config::time(int init) {

   unsigned short fps(4*frame_number_);

   std::string new_title("Release the kraken!   |   FPS : ");
   new_title.append(std::to_string(fps));

   glutSetWindowTitle(new_title.c_str());
   frame_number_ = 0;

   glutTimerFunc(250,time,0);
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

   pipeline_.uniforms_.set("projection",projection);
   pipeline_.uniforms_.set("view",view);

   pipeline_.set_link("glyph","projection");
   pipeline_.set_link("glyph","view");
   pipeline_.set_link("streamline","projection");
   pipeline_.set_link("streamline","view");
   pipeline_.set_link("bounding_box","projection");
   pipeline_.set_link("bounding_box","view");
}

void config::bind_field(vector_field const& vf) {
   
   // particle loading 
   GLuint vbo,vao;

   particle_emitter emitter;
   
   particles pos(emitter.raster(20,vf.dim_));

   particle_number_ = pos.size_ / (3 * sizeof(float));

   glGenBuffers(1,&vbo);
   glGenVertexArrays(1,&vao);

   glBindBuffer(GL_ARRAY_BUFFER,vbo);

   glBufferData(GL_ARRAY_BUFFER,pos.size_,pos.data_,GL_STATIC_DRAW);
   glBindVertexArray(vao);

   GLint attr_pos(glGetAttribLocation(1,"pos"));

   glEnableVertexAttribArray(attr_pos);
   glVertexAttribPointer(attr_pos,3,GL_FLOAT,GL_FALSE,0,0);

   float border_color[] = {0.0f,0.0f,0.0f,1.0f};

   GLuint tex_id;
   glGenTextures(1, &tex_id);
   glEnable(GL_TEXTURE_3D);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_3D, tex_id);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
   glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, border_color);
   glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB32F, 
                vf.dim_[0], vf.dim_[1], vf.dim_[2], 0, GL_RGB, 
                GL_FLOAT, vf.data_);

   glm::vec3 lightpos(0.0,0.0,5.0);
   pipeline_.uniforms_.set("lightpos", lightpos);
   pipeline_.set_link("glyph","lightpos");

   glm::vec2 interval(vf.min_,vf.max_);
   pipeline_.uniforms_.set("interval", interval);
   pipeline_.set_link("glyph","interval");
   pipeline_.set_link("streamline","interval");

   glm::ivec3 dim(vf.dim_[0],vf.dim_[1],vf.dim_[2]);
   pipeline_.uniforms_.set("dim", dim);
   pipeline_.set_link("glyph","dim");
   pipeline_.set_link("streamline","dim");
   pipeline_.set_link("bounding_box","dim");
}

pipeline config::pipeline_ = pipeline();
unsigned short config::frame_number_    = 0;
unsigned short config::particle_number_ = 0;
}
