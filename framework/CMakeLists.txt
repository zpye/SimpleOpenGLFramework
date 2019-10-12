cmake_minimum_required(VERSION 3.0)

# opengl libs
# glfw
add_subdirectory(glfw-3.3)

# glm
add_subdirectory(glm)
set_target_properties(glm_static PROPERTIES FOLDER "GLM")

# glad
set(glad_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad)
add_library(glad
${glad_dir}/glad.c
${glad_dir}/glad.h
${glad_dir}/khrplatform.h
)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(glad PROPERTIES FOLDER "GLAD")

set(GL_LIBS glm_static glad glfw)

# 3rdparty libs
# stb_image
add_subdirectory(stb_image)
list(APPEND GL_LIBS stb_image)

# assimp
option(BUILD_ASSIMP "build Open Asset Import Library" OFF)
if(BUILD_ASSIMP)
    add_subdirectory(assimp)
    set_target_properties(assimp PROPERTIES FOLDER "ASSIMP")
    set_target_properties(IrrXML PROPERTIES FOLDER "ASSIMP")
    set_target_properties(zlib PROPERTIES FOLDER "ASSIMP")
    set_target_properties(zlibstatic PROPERTIES FOLDER "ASSIMP")
    list(APPEND GL_LIBS assimp)
endif(BUILD_ASSIMP)

# build framework
set(framework_files
camera.cpp
camera.h
mesh.cpp
mesh.h
model.cpp
model.h
shader.cpp
shader.h
utils.cpp
utils.h
)

add_library(framework STATIC ${framework_files})
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(framework PUBLIC ${GL_LIBS})
target_compile_options(framework PUBLIC -DGLFW_INCLUDE_NONE)
