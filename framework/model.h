#ifndef FRAMEWORK_MODEL_H
#define FRAMEWORK_MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "mesh.h"
#include "shader.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory,
                             const bool& gamma = false);

class Model {
 public:
  // constructor, expects a filepath to a 3D model.
  Model(const std::string& path, const bool& gamma = false);

  // draws the model, and thus all its meshes
  void Draw(const Shader& shader) const;

 private:
  // loads a model with supported ASSIMP extensions from file and stores the
  // resulting meshes in the meshes vector.
  void loadModel(const std::string& path);

  // processes a node in a recursive fashion. Processes each individual mesh
  // located at the node and repeats this process on its children nodes (if
  // any).
  void processNode(aiNode* node, const aiScene* scene);

  Mesh processMesh(aiMesh* mesh, const aiScene* scene);

  // checks all material textures of a given type and loads the textures if
  // they're not loaded yet. the required info is returned as a Texture struct.
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
                                            const aiTextureType& type,
                                            const std::string& typeName);

 public:
  /*  Model Data */
  // stores all the textures loaded so far, optimization
  // to make sure textures aren't loaded more than once.
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;
  bool gammaCorrection;
};

#endif  // FRAMEWORK_MODEL_H
