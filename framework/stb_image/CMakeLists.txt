cmake_minimum_required(VERSION 3.0)

set(stb_image_files
stb_image.cpp
stb_image.h
stb_image_write.cpp
stb_image_write.h
)

add_library(stb_image STATIC ${stb_image_files})
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(stb_image PROPERTIES FOLDER "stb_image")
