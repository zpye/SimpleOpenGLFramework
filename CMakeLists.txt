cmake_minimum_required(VERSION 3.0)

project(SimpleOpenGLFramework)
# common compile options
add_compile_options(-DSHADER_PATH="${CMAKE_SOURCE_DIR}/shaders")
add_compile_options(-DRESOURCE_PATH="${CMAKE_SOURCE_DIR}/resources")
if(MSVC)
    add_compile_options(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

# framework
add_subdirectory(framework)

# samples
set(sample_path ${CMAKE_SOURCE_DIR}/samples)

add_executable(multiple_lights ${sample_path}/multiple_lights.cpp)
target_link_libraries(multiple_lights framework)
set_target_properties(multiple_lights PROPERTIES FOLDER "samples")

if(BUILD_ASSIMP)
    add_executable(model_loading ${sample_path}/model_loading.cpp)
    target_link_libraries(model_loading framework)
    set_target_properties(model_loading PROPERTIES FOLDER "samples")
endif(BUILD_ASSIMP)