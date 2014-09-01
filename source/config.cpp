#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <config.hpp>
#include <particle_emitter.hpp>


namespace kraken {

// init static member
pipeline config::pipeline_ = pipeline();

std::array<GLuint,2> config::buffer_ = {{0,0}};

std::array<GLuint,2> config::array_ptr_ = {{0,0}};

GLuint config::tex_id_ = 0;

unsigned short config::frame_number_    = 0;
unsigned short config::particle_number_ = 0;

float config::aspect_ratio_ = 0.0f;
float config::depth_ = -300.0f;

std::array<float,2> config::rot_ = {{0.0f,0.0f}};

bool config::dirty_ = true;

bool config::bbox_ = false;

bool config::switch_ = true;

std::string config::program_ = "streamline";


// callback functions
void config::

display() {

   if(dirty_ || switch_) {

      if(switch_) {

         pipeline_.enable(program_);

         switch_ = false;
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDrawArrays(GL_POINTS,0,particle_number_);

      if(bbox_) {

         glBindVertexArray(array_ptr_[0]);

         pipeline_.enable("bounding_box");

         glDrawArrays(GL_POINTS,0,1);

         glBindVertexArray(array_ptr_[1]);

         pipeline_.enable(program_);
      }

      glutSwapBuffers();

      dirty_ = false;
   }

   glutPostRedisplay();

   ++frame_number_;
}


void config::

key(unsigned char key,int x,int y) {

   unsigned short key_id(static_cast<unsigned short> (key));

   switch(key_id) {

      case  27 : glutLeaveMainLoop(); break;

      case  43 : depth_ += 0.5f; init_perspective(); switch_ = true; break;

      case  45 : depth_ -= 0.5f; init_perspective(); switch_ = true; break;

      case  49 : program_ = "glyph"; switch_ = true ; break;

      case  50 : program_ = "streamline"; switch_ = true; break;

      case  98 : bbox_  = !bbox_; dirty_ = true; break;

      case 114 : pipeline_.link_programs(); switch_ = true; break;
   }
}


void config::

special_key(int key_id,int x,int y) {

   switch(key_id) {

      case 100 : rot_[1] -= 0.01f; init_perspective(); switch_ = true; break;

      case 101 : rot_[0] -= 0.01f; init_perspective(); switch_ = true; break;

      case 102 : rot_[1] += 0.01f; init_perspective(); switch_ = true; break;

      case 103 : rot_[0] += 0.01f; init_perspective(); switch_ = true; break;
   }
}


void config::

time(int init) {

   unsigned short fps(4 * frame_number_);

   std::string new_title("Release the kraken!   |   FPS : ");
   new_title.append(std::to_string(fps));

   glutSetWindowTitle(new_title.c_str());
   frame_number_ = 0;

   glutTimerFunc(250,time,0);
}

void config::resize(int width, int height) {
   
   aspect_ratio_ = static_cast<float> (width) / height;
   init_perspective();
   glViewport(0, 0, width, height);
   switch_ = true;

}

// support functions
void config::

init(float aspect_ratio) {

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_MULTISAMPLE_ARB);
   glClearColor(0.2,0.2,0.2,1.0);

   aspect_ratio_ = aspect_ratio;

   init_programs();
   init_uniforms();
}


void config::bind_field(vector_field const& vf) {
   
   glm::vec2 interval(vf.min_,vf.max_);
   pipeline_.uniforms_.set("interval", interval);
   pipeline_.set_link("glyph","interval");
   pipeline_.set_link("streamline","interval");

   glm::ivec3 dim(vf.dim_[0],vf.dim_[1],vf.dim_[2]);
   pipeline_.uniforms_.set("dim", dim);
   pipeline_.set_link("glyph","dim");
   pipeline_.set_link("streamline","dim");
   pipeline_.set_link("bounding_box","dim");

   init_memory(vf.dim_);
   init_texture(vf);
}


void config::clear() {

   for(auto it(array_ptr_.begin()) ; it != array_ptr_.end() ; ++it) {

      GLuint id(*it);

      glDeleteVertexArrays(1,&id);
   }

   for(auto it(buffer_.begin()) ; it != buffer_.end() ; ++it) {

      GLuint id(*it);

      glDeleteBuffers(1,&id);
   }

   glDeleteTextures(1,&tex_id_);
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

init_uniforms() {

   glm::vec3 lightpos(0.0,0.0,5.0);

   pipeline_.uniforms_.set("lightpos", lightpos);

   init_perspective();

   pipeline_.set_link("glyph","perspective_view");
   pipeline_.set_link("glyph","lightpos");
   pipeline_.set_link("streamline","perspective_view");
   pipeline_.set_link("bounding_box","perspective_view");
}


void config::

init_perspective() {

   glm::mat4 projection(glm::perspective(45.0f,aspect_ratio_,1.0f,500.0f)),

             view(glm::rotate(glm::mat4(),rot_[0],glm::vec3(1.0f,0.0f,0.0f)));

   view = glm::rotate(view,rot_[1],glm::vec3(0.0f,1.0f,0.0f));

   view[3][2] = depth_;

   glm::mat4 perspective_view(projection * view);

   pipeline_.uniforms_.set("perspective_view",perspective_view);

}


void config::

init_memory(std::array<unsigned short,3> const& dim) {

   GLuint vbo[2],vao[2];

   // generate particles
   particle_emitter emitter;
   
   particles pos(emitter.raster(40,dim));

   particle_number_ = pos.size_ / (3 * sizeof(float));


   // buffer center position

   float center[3] = {0.0,0.0,0.0};

   glGenBuffers(2,&vbo[0]);

   glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);

   glBufferData(GL_ARRAY_BUFFER,sizeof(center),&center[0],GL_STATIC_DRAW);


   // build attribute pointer for center

   glGenVertexArrays(2,&vao[0]);

   glBindVertexArray(vao[0]);

   glEnableVertexAttribArray(0);

   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);  


   // buffer particle positions

   glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);

   glBufferData(GL_ARRAY_BUFFER,pos.size_,pos.data_,GL_STATIC_DRAW);


   // build attribute pointer for particle positions

   glBindVertexArray(vao[1]);

   glEnableVertexAttribArray(0);

   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);


   // save buffer id

   buffer_[0] = vbo[0];
   buffer_[1] = vbo[1];

   array_ptr_[0] = vao[0];
   array_ptr_[1] = vao[1];
}


void config::

init_texture(vector_field const& vf) {

   float border_color[] = {0.0f,0.0f,0.0f,1.0f};

   glGenTextures(1, &tex_id_);

   glEnable(GL_TEXTURE_3D);
   glActiveTexture(GL_TEXTURE0);

   glBindTexture(GL_TEXTURE_3D, tex_id_);

   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
   glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, border_color);

   glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB32F,
                vf.dim_[0], vf.dim_[1], vf.dim_[2],
                0, GL_RGB, GL_FLOAT, vf.data_);
}

}
