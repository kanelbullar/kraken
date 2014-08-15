g++ main.cpp\
   source/exception.cpp\
   source/gl_config.cpp\
   source/vector_field.cpp\
   source/vector_field_generator.cpp\
   source/pipeline.cpp\
   source/progress.cpp\
   source/window.cpp\
   -omain -std=c++11 -Wall -pedantic\
   -Iinclude\
   -lpthread -lGL -lGLEW -lglut -lm -lstdc++ 
