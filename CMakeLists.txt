cmake_minimum_required(VERSION 3.0)

# settings properties before call project command
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

add_executable(blending_sorted ${sample_path}/blending_sorted.cpp)
target_link_libraries(blending_sorted framework)
set_target_properties(blending_sorted PROPERTIES FOLDER "samples")

add_executable(cubemaps_environment_mapping ${sample_path}/cubemaps_environment_mapping.cpp)
target_link_libraries(cubemaps_environment_mapping framework)
set_target_properties(cubemaps_environment_mapping PROPERTIES FOLDER "samples")

add_executable(anti_aliasing_offscreen ${sample_path}/anti_aliasing_offscreen.cpp)
target_link_libraries(anti_aliasing_offscreen framework)
set_target_properties(anti_aliasing_offscreen PROPERTIES FOLDER "samples")

add_executable(shadow_mapping ${sample_path}/shadow_mapping.cpp)
target_link_libraries(shadow_mapping framework)
set_target_properties(shadow_mapping PROPERTIES FOLDER "samples")

add_executable(point_shadows_soft ${sample_path}/point_shadows_soft.cpp)
target_link_libraries(point_shadows_soft framework)
set_target_properties(point_shadows_soft PROPERTIES FOLDER "samples")

add_executable(normal_mapping ${sample_path}/normal_mapping.cpp)
target_link_libraries(normal_mapping framework)
set_target_properties(normal_mapping PROPERTIES FOLDER "samples")

add_executable(parallax_occlusion_mapping ${sample_path}/parallax_occlusion_mapping.cpp)
target_link_libraries(parallax_occlusion_mapping framework)
set_target_properties(parallax_occlusion_mapping PROPERTIES FOLDER "samples")

add_executable(debugging ${sample_path}/debugging.cpp)
target_link_libraries(debugging framework)
set_target_properties(debugging PROPERTIES FOLDER "samples")

if(BUILD_ASSIMP)
    add_executable(model_loading ${sample_path}/model_loading.cpp)
    target_link_libraries(model_loading framework)
    set_target_properties(model_loading PROPERTIES FOLDER "samples")
endif(BUILD_ASSIMP)

if(BUILD_ASSIMP)
    add_executable(geometry_shader_exploding_normal_visualization ${sample_path}/geometry_shader_exploding_normal_visualization.cpp)
    target_link_libraries(geometry_shader_exploding_normal_visualization framework)
    set_target_properties(geometry_shader_exploding_normal_visualization PROPERTIES FOLDER "samples")
endif(BUILD_ASSIMP)

if(BUILD_ASSIMP)
    add_executable(asteroids_instanced ${sample_path}/asteroids_instanced.cpp)
    target_link_libraries(asteroids_instanced framework)
    set_target_properties(asteroids_instanced PROPERTIES FOLDER "samples")
endif(BUILD_ASSIMP)

if(BUILD_ASSIMP)
    add_executable(deferred_shading_volumes ${sample_path}/deferred_shading_volumes.cpp)
    target_link_libraries(deferred_shading_volumes framework)
    set_target_properties(deferred_shading_volumes PROPERTIES FOLDER "samples")
endif(BUILD_ASSIMP)
