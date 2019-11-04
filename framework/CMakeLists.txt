cmake_minimum_required(VERSION 3.0)

# opengl libs
option(USE_EGL "build opengles with egl" OFF)
set(GL_LIBS "")

# glfw
if(NOT USE_EGL)
    add_subdirectory(glfw-3.3)
    list(APPEND GL_LIBS glfw)
endif()

# glm
add_subdirectory(glm)
set_target_properties(glm_static PROPERTIES FOLDER "GLM")
list(APPEND GL_LIBS glm_static)

# glad
if(NOT USE_EGL)
    set(glad_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad)
    add_library(glad
    ${glad_dir}/glad.c
    ${glad_dir}/glad.h
    ${glad_dir}/khrplatform.h
    )
    target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
else()
    set(glad_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad-es/src)
    add_library(glad
    ${glad_dir}/egl.c
    ${glad_dir}/gles.c
    )
    target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad-es/include)
endif()
set_target_properties(glad PROPERTIES FOLDER "GLAD")
list(APPEND GL_LIBS glad)

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
shader.cpp
shader.h
utils.cpp
utils.h
)

if(BUILD_ASSIMP)
    list(APPEND framework_files model.cpp model.h)
endif(BUILD_ASSIMP)

add_library(framework STATIC ${framework_files})
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(framework PUBLIC ${GL_LIBS})
target_compile_options(framework PUBLIC -DGLFW_INCLUDE_NONE)
set_target_properties(framework PROPERTIES FOLDER "framework")
