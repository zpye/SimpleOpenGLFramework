#ifndef FRAMEWORK_MESH_H
#define FRAMEWORK_MESH_H

#include <glad/glad.h>  // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Vertex {
  // position
  glm::vec3 Position;
  // normal
  glm::vec3 Normal;
  // texCoords
  glm::vec2 TexCoords;
  // tangent
  glm::vec3 Tangent;
  // bitangent
  glm::vec3 Bitangent;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
 public:
  // constructor
  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices,
       const std::vector<Texture>& textures);

  // render the mesh
  void Draw(const Shader& shader) const;

 private:
  // initializes all the buffer objects/arrays
  void setupMesh();

 public:
  // Mesh Data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  unsigned int VAO;

 private:
  // Render data
  unsigned int VBO, EBO;
};

#endif  // FRAMEWORK_MESH_H
