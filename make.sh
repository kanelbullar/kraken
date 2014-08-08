g++ main.cpp\
   source/exception.cpp\
   source/vector_field.cpp\
   source/vector_field_generator.cpp\
   source/pipeline.cpp\
   source/window.cpp\
   -omain -std=c++11 -Wall -pedantic\
   -Iinclude -I../glfw/include\
   -L../glfw/src\
   -lglfw3 -lGL -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXcursor -lXi
