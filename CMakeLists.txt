cmake_minimum_required(VERSION 4.1)
project(ModelagemHierarquica)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ModelagemHierarquica
        main.cpp
        /home/unir3/external/glad/src/glad.c

)

target_include_directories(ModelagemHierarquica PRIVATE
        /home/unir3/external/glad/include
)

target_link_libraries(ModelagemHierarquica PRIVATE
        OpenGL::GL
        glfw
)