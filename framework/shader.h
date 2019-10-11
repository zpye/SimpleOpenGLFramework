#ifndef FRAMEWORK_SHADER_H
#define FRAMEWORK_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  // constructor generates the shader on the fly
  Shader(const char* vertexPath, const char* fragmentPath,
         const char* geometryPath = nullptr);

  // activate the shader
  void use() const;

  // utility uniform functions
  void setBool(const std::string& name, const bool& value) const;

  void setInt(const std::string& name, const int& value) const;

  void setFloat(const std::string& name, const float& value) const;

  void setVec2(const std::string& name, const glm::vec2& value) const;
  void setVec2(const std::string& name, const float& x, const float& y) const;

  void setVec3(const std::string& name, const glm::vec3& value) const;
  void setVec3(const std::string& name, const float& x, const float& y,
               const float& z) const;

  void setVec4(const std::string& name, const glm::vec4& value) const;
  void setVec4(const std::string& name, const float& x, const float& y,
               const float& z, const float& w) const;

  void setMat2(const std::string& name, const glm::mat2& mat) const;

  void setMat3(const std::string& name, const glm::mat3& mat) const;

  void setMat4(const std::string& name, const glm::mat4& mat) const;

 public:
  unsigned int ID;

 private:
  // utility function for checking shader compilation/linking errors.
  void checkCompileErrors(const GLuint& shader, const std::string& type) const;
};

#endif  // FRAMEWORK_SHADER_H
