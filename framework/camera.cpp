#include "camera.h"

// Constructor with vectors
Camera::Camera(const glm::vec3& position, const glm::vec3& up, const float& yaw,
               const float& pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;

  updateCameraVectors();
}

// Constructor with scalar values
Camera::Camera(const float& posX, const float& posY, const float& posZ,
               const float& upX, const float& upY, const float& upZ,
               const float& yaw, const float& pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM) {
  Position = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;

  updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system. Accepts input
// parameter in the form of camera defined ENUM (to abstract it from windowing
// systems)
void Camera::ProcessKeyboard(const Camera_Movement& direction,
                             const float& deltaTime) {
  float velocity = MovementSpeed * deltaTime;

  if (direction == kFORWARD) {
    Position += Front * velocity;
  } else if (direction == kBACKWARD) {
    Position -= Front * velocity;
  } else if (direction == kLEFT) {
    Position -= Right * velocity;
  } else if (direction == kRIGHT) {
    Position += Right * velocity;
  }
}

// Processes input received from a mouse input system. Expects the offset
// value in both the x and y direction.
void Camera::ProcessMouseMovement(const float& xoffset, const float& yoffset,
                                  const GLboolean& constrainPitch) {
  Yaw += xoffset * MouseSensitivity;
  Pitch += yoffset * MouseSensitivity;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (Pitch > 89.0f) {
      Pitch = 89.0f;
    } else if (Pitch < -89.0f) {
      Pitch = -89.0f;
    }
  }

  // Update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires
// input on the vertical wheel-axis
void Camera::ProcessMouseScroll(const float& yoffset) {
  if (Zoom >= 1.0f && Zoom <= 45.0f) {
    Zoom -= yoffset;
  }

  if (Zoom < 1.0f) {
    Zoom = 1.0f;
  }

  if (Zoom > 45.0f) {
    Zoom = 45.0f;
  }
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors() {
  // Calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);

  // Also re-calculate the Right and Up vector
  Right = glm::normalize(glm::cross(Front, WorldUp));

  // Normalize the vectors, because their length gets
  // closer to 0 the more you look up or down which
  // results in slower movement.
  Up = glm::normalize(glm::cross(Right, Front));
}
