#ifndef FRAMEWORK_CAMERA_H
#define FRAMEWORK_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to
// stay away from window-system specific input methods
enum Camera_Movement { kFORWARD, kBACKWARD, kLEFT, kRIGHT };

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
 public:
  // Constructor with vectors
  Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
         const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
         const float& yaw = YAW, const float& pitch = PITCH);

  // Constructor with scalar values
  Camera(const float& posX, const float& posY, const float& posZ,
         const float& upX, const float& upY, const float& upZ, const float& yaw,
         const float& pitch);

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 GetViewMatrix();

  // Processes input received from any keyboard-like input system. Accepts input
  // parameter in the form of camera defined ENUM (to abstract it from windowing
  // systems)
  void ProcessKeyboard(const Camera_Movement& direction,
                       const float& deltaTime);

  // Processes input received from a mouse input system. Expects the offset
  // value in both the x and y direction.
  void ProcessMouseMovement(const float& xoffset, const float& yoffset,
                            const GLboolean& constrainPitch = true);

  // Processes input received from a mouse scroll-wheel event. Only requires
  // input on the vertical wheel-axis
  void ProcessMouseScroll(const float& yoffset);

 public:
  // Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  // Euler Angles
  float Yaw;
  float Pitch;

  // Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

 private:
  // Calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors();
};

#endif  // FRAMEWORK_CAMERA_H
