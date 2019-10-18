#include "utils.h"

#include <glad/glad.h>

#include "stb_image.h"
#include "stb_image_write.h"

#include <ctime>
#include <iostream>

// utility function for loading a 2D texture from file
unsigned int loadTexture(char const* path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format = GL_NONE;
    if (nrComponents == 1) {
      format = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
unsigned int loadCubemap(std::vector<std::string> faces) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrComponents;
  for (unsigned int i = 0; i < faces.size(); ++i) {
    unsigned char* data =
        stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Cubemap texture failed to load at path: " << faces[i]
                << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}

/*
Copyright (c) 2018 Christian Vallentin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
// referred to https://vallentin.io/2013/09/02/opengl-screenshot
// https://github.com/vallentin/GLCollection/blob/master/screenshot.cpp
const char* createScreenshotBasename() {
  static char basename[50];

  time_t t = time(NULL);
  strftime(basename, 50, "%Y%m%d_%H%M%S.png", localtime(&t));

  return basename;
}

// referred to https://vallentin.io/2013/09/02/opengl-screenshot
// https://github.com/vallentin/GLCollection/blob/master/screenshot.cpp
int saveScreenshot(const char* filename) {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  int x = viewport[0];
  int y = viewport[1];
  int width = viewport[2];
  int height = viewport[3];

  // 3 components (R, G, B)
  char* data = (char*)malloc((size_t)(width * height * 3));
  if (!data) {
    return 0;
  }

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  stbi_flip_vertically_on_write(1);

  int saved = stbi_write_png(filename, width, height, 3, data, 0);

  free(data);

  return saved;
}