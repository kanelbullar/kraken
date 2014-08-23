#include <stage.hpp>

#include <iostream>
#include <fstream>


stage::

stage(std::string const& path) :
id_(0),
type_(GL_INVALID_ENUM),
path_(path)
{
  type_ = recognize_type();
}


stage::

~stage()
{
  clear();
}


GLuint stage::

compile()
{
  if(id_ != 0)
  {
    clear();
  }

  if(type_ != GL_INVALID_ENUM)
  {
    const char* source(load());

    if(source != nullptr)
    {
      id_ = glCreateShader(type_);

      if(id_ != 0)
      {
        glShaderSource(id_,1,&source,nullptr);
        glCompileShader(id_);

        if(!compile_feedback())
        {
          clear();
        }
      }
    }

    delete[] source;
  }

  return id_;
}


bool stage::

equal(std::string const& path) const
{
  if(path_.compare(path) == 0) return true;

  return false;
}


GLenum stage::

id() const
{
  return id_;
}


GLenum stage::

type() const
{
  return type_;
}


void stage::

clear()
{
  if(id_ != 0)
  {
    glDeleteShader(id_);

    id_ = 0;
  }
}


const GLchar* const stage::

load() const
{
  GLchar* source(nullptr);

  std::ifstream input(path_);

  if(input.good())
  {
    unsigned short length(0);

    input.seekg(0,input.end);
    length = input.tellg();
    input.seekg(0,input.beg);

    if(length != 0)
    {
      source = new char[length - 1];

      input.get(source,length,EOF);

      if(input.gcount() != length - 1)
      {
        std::cerr << std::endl
                  << "failed to load " << path_
                  << std::endl;

        delete[] source;

        source = nullptr;
      }
    }

    input.close();
  }

  else
  {
    std::cerr << std::endl
              << "file " << path_ << " doesn't exist"
              << std::endl;
  }

  return source;
}

bool stage::

compile_feedback() const
{
  GLint status(GL_FALSE);

  glGetShaderiv(id_,GL_COMPILE_STATUS,&status);

  if(status != GL_TRUE)
  {
    GLint   length(0);
    GLchar* info_buffer(nullptr);

    glGetShaderiv(id_,GL_INFO_LOG_LENGTH,&length);

    if(length != 0)
    {
      info_buffer = new GLchar[length];

      glGetShaderInfoLog(id_,length,nullptr,info_buffer);

      std::cerr << std::endl
                << "[" << path_ << "]"
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

GLenum stage::

recognize_type() const
{
  GLenum type(GL_INVALID_ENUM);

  size_t suffix_pos(path_.rfind('.'));

  if(suffix_pos != std::string::npos)
  {
    ++suffix_pos;

    size_t suffix_length(path_.length() - suffix_pos);

    std::string suffix(path_.substr(suffix_pos,suffix_length));

    if     (suffix.compare("vert") == 0) type = GL_VERTEX_SHADER;
    else if(suffix.compare("geom") == 0) type = GL_GEOMETRY_SHADER;
    else if(suffix.compare("frag") == 0) type = GL_FRAGMENT_SHADER;

    else
    {
      std::cerr << std::endl
                << "invalid stage suffix : " << path_
                << std::endl;
    }
  }

  else
  {
      std::cerr << std::endl
                << "missing stage suffix : " << path_
                << std::endl;
  }

  return type;
}
