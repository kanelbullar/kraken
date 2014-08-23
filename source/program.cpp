#include <program.hpp>

#include <iostream>


program::

program(std::string const& name) :
id_(0),
name_(name),
stages_()
{}


program::

~program()
{
  clear();
}


void program::

link()
{
  if(id_ != 0) clear();

  id_ = glCreateProgram();

  if(id_ != 0)
  {
    for(auto it(stages_.begin()) ; it != stages_.end() ; ++it)
    {
      stage* stage_ptr(it->get());

      if(stage_ptr != nullptr)
      {
        GLuint stage_id(stage_ptr->compile());

        if(stage_id != 0) glAttachShader(id_,stage_id);
      }
    }

    glLinkProgram(id_);
    clear_stages();

    if(!link_feedback()) clear();
  }
}


void program::

reset_stage(GLenum type)
{
  switch(type)
  {
    case GL_VERTEX_SHADER :

    if(stages_[0].get() != nullptr) stages_[0].reset();
    break;

    case GL_GEOMETRY_SHADER :

    if(stages_[3].get() != nullptr) stages_[3].reset();
    break;

    case GL_FRAGMENT_SHADER :

    if(stages_[4].get() != nullptr) stages_[4].reset();
    break;
  }
}


void program::

define_stage(std::shared_ptr<stage> & stage_ptr)
{
  switch(stage_ptr->type())
  {
    case GL_VERTEX_SHADER :

    stages_[0].swap(stage_ptr);
    break;

    case GL_GEOMETRY_SHADER :

    stages_[3].swap(stage_ptr);
    break;

    case GL_FRAGMENT_SHADER :

    stages_[4].swap(stage_ptr);
    break;
  }
}


bool program::

equal(std::string const& name) const
{
  if(name_.compare(name) == 0) return true;

  return false;
}


GLuint program::

id() const
{
  return id_;
}


void program::

clear()
{
  glDeleteProgram(id_);

  id_ = 0;
}


void program::

clear_stages() const
{
  for(auto it(stages_.begin()) ; it != stages_.end() ; ++it)
  {
    stage* stage_ptr(it->get());

    if(stage_ptr != nullptr)
    {
      if(id_ != 0) glDetachShader(id_,stage_ptr->id());

      stage_ptr->clear();
    }
  }
}


bool program::

link_feedback() const
{
  GLint link_status(GL_FALSE);

  glGetProgramiv(id_,GL_LINK_STATUS,&link_status);

  if(link_status != GL_TRUE)
  {
    GLint   length(0);
    GLchar* info_buffer(nullptr);

    glGetProgramiv(id_,GL_INFO_LOG_LENGTH,&length);

    if(length != 0)
    {
      info_buffer = new GLchar[length];

      glGetProgramInfoLog(id_,length,&length,info_buffer);

      std::cerr << std::endl
                << "[" << name_ << "]"
                << std::endl << std::endl
                << "line " << info_buffer
                << std::endl;

      delete[] info_buffer;
    }

    return false;
  }

  else
  {
    return true;
  }
}
